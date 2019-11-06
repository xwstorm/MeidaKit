//
//  video_render_manager_base.cpp
//  Pods
//
//  Created by xiewei on 2019/11/6.
//

#include "video_render_manager_base.h"
MK_BEGIN
VideoRenderManagerBase::VideoRenderManagerBase()
: mRenderThread("video_render")
{
    
}

int VideoRenderManagerBase::open() {
    mRenderThread.open();
    return 0;
}

void VideoRenderManagerBase::close() {
    // cancal task
    
    // destroy OpenGL context
    mRenderThread.close();
}

MK_END
