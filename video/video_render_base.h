//
//  video_render_base.h
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#pragma once
#include "base/mk_base.h"
#include "base/mk_thread.h"
#include "video/mk_video_frame.h"
MK_BEGIN
class MKView;
class VideoRenderBase {
public:
    VideoRenderBase();
    virtual int open();
    virtual void close();
    virtual int updateFrame(std::string streamId, MKVideoFrame* videoFrame);
    int setView(std::string streamId, MKView* view);
protected:
    
protected:
    MKThread mRenderThread;
    std::atomic_short mState;
};
MK_END
