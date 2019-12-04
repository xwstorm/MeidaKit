//
//  video_render_egl_ios.hpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#pragma once
#include "video/render_manager_egl.h"
#include "mk_video_render_program_egl.h"

MK_BEGIN
class MKEglRenderManager : public BRenderManagerEgl {
public:
    MKEglRenderManager();
    ~MKEglRenderManager();
    
    int updateFrame(std::string streamId, CVPixelBufferRef videoFrame);
    
    int updateFrame(std::string streamId, BVideoFrame* videoFrame) override;
protected:
    
    VideoRenderEgl* CreateVideoRender() override;
};
MK_END
