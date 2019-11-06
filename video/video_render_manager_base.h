//
//  video_render_manager_base.hpp
//  Pods
//
//  Created by xiewei on 2019/11/6.
//

#pragma once
#include "base/mk_base.h"
#include "base/mk_thread.h"
MK_BEGIN
class VideoRenderManagerBase {
public:
    VideoRenderManagerBase();
    virtual int open();
    virtual void close();
protected:
    
protected:
    MKThread mRenderThread;
};
MK_END
