//
//  video_render_manager.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/4.
//

#include "render_manager_egl.h"
#include "base/location.h"
#include "video_render_program_egl.h"

MK_BEGIN
BRenderManagerEgl::BRenderManagerEgl()
: mRenderInterval(33) {
    
}

int BRenderManagerEgl::open() {
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

void BRenderManagerEgl::close() {
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

int BRenderManagerEgl::updateView(std::string streamId, MKView* view) {
    mRenderThread.Invoke<void>(CALL_FROM_HERE, [this, streamId, view](){
        auto it = mResourceMap.find(streamId);
        if (view == nullptr) {
            // clear internal view
            if (it != mResourceMap.end()) {
                it->second->updateView(nullptr);
            }
        } else {
            VideoRenderEgl* eglRender = nullptr;
            if (it == mResourceMap.end()) {
                // create new render
                assert(false);// TODO
            } else {
                eglRender = it->second;
            }
            eglRender->updateView(view);
        }
    });
    return S_OK;
}

int BRenderManagerEgl::updateFrame(std::string streamId, BVideoFrame* videoFrame) {
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
            
            it->second->updateFrame(nullptr);
            if (it->second->view() == nullptr) {
                mResourceMap.erase(it);
            }
        });
    } else {
        mRenderThread.AsyncInvoke<void>(CALL_FROM_HERE, [this, streamId, videoFrame]() {
            mResourceMap[streamId]->updateFrame(videoFrame);
        });
    }
    return S_OK;
}

void BRenderManagerEgl::render() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastRenderTime).count();
    mLastRenderTime = now;
    printf("video render: %lld\n", elapsed);
    
    for(auto it=mResourceMap.begin(); it != mResourceMap.end(); ++it) {
        VideoRenderEgl* eglRender = it->second;
        if (eglRender->view()) {
            if (!eglRender->dirty()) {
                continue;
            }
            if(mEGLEnv->bindView(eglRender->view()) == S_OK) {
                // render
                eglRender->Render();
            } else {
                assert(false);
            }
        } else {
            // warning,
        }
    }
    
    postDelayTask();
}

void BRenderManagerEgl::postDelayTask() {
    if (mState == MKStateOpened) {
        mRenderThread.AsyncInvokeDelay<void>(CALL_FROM_HERE, [this]() {
            render();
        }, mRenderInterval);
    }
}

void BRenderManagerEgl::setRenderInterval(int interval) {
    mRenderInterval = interval;
}
MK_END
