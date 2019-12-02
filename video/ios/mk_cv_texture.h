//
//  mk_cv_texture.hpp
//  Pods
//
//  Created by xiewei on 2019/11/28.
//

#pragma once
#include "base/mk_base.h"
#include "video/video_texture.h"
#import <CoreVideo/CVPixelBuffer.h>

MK_BEGIN
class MKCVTexture : public VideoTexture {
public:
    int updateFrame(CVPixelBufferRef buffer);
    
    uint32_t GetTextureId(int index) override;
    
};
MK_END
