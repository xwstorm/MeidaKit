//
//  video_render_manager.hpp
//  Pods
//
//  Created by xiewei on 2019/11/4.
//

#pragma once
#include "video/video_render_manager_base.h"

MK_BEGIN
class VideoEGLRenderManager : public VideoRenderManagerBase {
public:
    VideoEGLRenderManager();
    int open() override;
    void close() override;
protected:
    void render();
    
protected:
    std::chrono::system_clock::time_point mLastRenderTime;
};

MK_END
