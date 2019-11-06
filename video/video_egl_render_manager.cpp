//
//  video_render_manager.cpp
//  Pods
//
//  Created by xiewei on 2019/11/4.
//

#include "video_egl_render_manager.h"
#include "base/location.h"
MK_BEGIN
VideoEGLRenderManager::VideoEGLRenderManager() {
    
}

int VideoEGLRenderManager::open() {
    int ret = VideoRenderManagerBase::open();
    if (ret != S_OK) {
        return ret;
    }
    // create OpenGL Context

    
    mRenderThread.AsyncInvokeDelay<void>(CALL_FROM_HERE, [this]() {
        render();
    }, 2000);
    
    return 0;
}

void VideoEGLRenderManager::close() {
    // cancal task
    
    // destroy OpenGL context sync
    
    
    mRenderThread.close();
}


void VideoEGLRenderManager::render() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastRenderTime).count();
    mLastRenderTime = now;
    printf("video render: %lld\n", elapsed);
    mRenderThread.AsyncInvokeDelay<void>(CALL_FROM_HERE, [this]() {
        render();
    }, 2000);
}
MK_END
