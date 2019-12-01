//
//  video_render_egl_ios.hpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#pragma once
#include "video/video_render_egl.h"

MK_BEGIN
class MKVideoRenderEgl : public BVideoRenderEgl {
public:
    MKVideoRenderEgl();
    ~MKVideoRenderEgl();
    
    int updateFrame(std::string streamId, CVPixelBufferRef videoFrame);
    
    int updateFrame(std::string streamId, BVideoFrame* videoFrame) override;
protected:
    
};
MK_END
