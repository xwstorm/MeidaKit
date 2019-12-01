//
//  video_render_manager.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/4.
//

#include "video_render_egl.h"
#include "base/location.h"
#include "video_render_program_egl.h"

MK_BEGIN
BVideoRenderEgl::BVideoRenderEgl()
: mRenderInterval(33) {
    
}

int BVideoRenderEgl::open() {
    if (mState == MKStateOpened) {
        return S_OK;
    }
    
    int ret = BVideoRender::open();
    if (ret != S_OK) {
        return ret;
    }
    // create OpenGL Context
    ret = mRenderThread.Invoke<int>(CALL_FROM_HERE, [this] () {
        return mEGLEnv->open(nullptr);
    });
    
    // init renderer
    postDelayTask();
    
    return S_OK;
}

void BVideoRenderEgl::close() {
    std::unique_lock<std::mutex> lock(mMapMutex);
    mState = MKStateClosed;
    lock.unlock();
    // clear all buffer
    
    // cancal task
    
    // destroy OpenGL context sync
    mRenderThread.Invoke<void>(CALL_FROM_HERE, [this] () {
        mEGLEnv->close();
    });
    
    mRenderThread.close();
}

int BVideoRenderEgl::updateView(std::string streamId, MKView* view) {
    mRenderThread.Invoke<void>(CALL_FROM_HERE, [this, streamId, view](){
        if (view == nullptr) {
            // clear internal view
            auto it = mResourceMap.find(streamId);
            if (it != mResourceMap.end()) {
                it->second.updateView(nullptr);
                if (it->second.frame() == nullptr) {
                    mResourceMap.erase(it);
                }
            }
            mEGLEnv->bindView(view);
        } else {
            mResourceMap[streamId].updateView(view);
        }
    });
    return S_OK;
}

int BVideoRenderEgl::updateFrame(std::string streamId, BVideoFrame* videoFrame) {
    if (mState == MKStateClosed) {
        return S_FAIL;
    }
    if (videoFrame == nullptr) {
        // clear data
        mRenderThread.Invoke<void>(CALL_FROM_HERE, [this, streamId](){
            auto it = mResourceMap.find(streamId);
            if (it == mResourceMap.end()) {
                return;
            }
            
            it->second.updateFrame(nullptr);
            if (it->second.view() == nullptr) {
                mResourceMap.erase(it);
            }
        });
    }
    
    mRenderThread.AsyncInvoke<void>(CALL_FROM_HERE, [this, streamId, videoFrame]() {
        mResourceMap[streamId].updateFrame(videoFrame);
    });
    
    return S_OK;
}

void BVideoRenderEgl::render() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastRenderTime).count();
    mLastRenderTime = now;
    printf("video render: %lld\n", elapsed);
    
    for(auto it=mResourceMap.begin(); it != mResourceMap.end(); ++it) {
        RenderResource& resource = it->second;
        if (resource.view()) {
            if (!resource.dirty()) {
                continue;
            }
            if(mEGLEnv->bindView(resource.view()) == S_OK) {
                // render
                if (mRenderer) {
                    mRenderer->render(resource.frame());
                }
            } else {
                assert(false);
            }
        } else {
            // warning,
        }
    }
    
    postDelayTask();
}

void BVideoRenderEgl::postDelayTask() {
    if (mState == MKStateOpened) {
        mRenderThread.AsyncInvokeDelay<void>(CALL_FROM_HERE, [this]() {
            render();
        }, mRenderInterval);
    }
}

void BVideoRenderEgl::setRenderInterval(int interval) {
    mRenderInterval = interval;
}
MK_END
