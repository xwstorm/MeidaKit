//
//  video_render_manager_base.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#include "render_manager_base.h"
MK_BEGIN
BVideoRender::BVideoRender()
: mRenderThread("video_render")
, mState(MKStateClosed)
{
    
}

int BVideoRender::open() {
    if (mState == MKStateOpened) {
        return S_OK;
    }
    mState = MKStateOpened;
    mRenderThread.open();
    return 0;
}

void BVideoRender::close() {
    
    mRenderThread.close();
    mState = MKStateClosed;
}

int BVideoRender::updateFrame(std::string streamId, BVideoFrame* videoFrame) {
    return S_OK;
}

int BVideoRender::setView(std::string streamId, MKView* view) {
    return S_OK;
}
MK_END
