//
//  video_render_manager_base.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#include "video_render_base.h"
MK_BEGIN
VideoRenderBase::VideoRenderBase()
: mRenderThread("video_render")
, mState(MKStateClosed)
{
    
}

int VideoRenderBase::open() {
    if (mState == MKStateOpened) {
        return S_OK;
    }
    mState = MKStateOpened;
    mRenderThread.open();
    return 0;
}

void VideoRenderBase::close() {
    
    mRenderThread.close();
    mState = MKStateClosed;
}

int VideoRenderBase::updateFrame(std::string streamId, MKVideoFrame* videoFrame) {
    return S_OK;
}

MK_END
