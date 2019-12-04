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
    ~MKCVTexture();
    int updateFrame(CVPixelBufferRef buffer);
    int updateFrame(BVideoFrame* frame) override;
    
    uint32_t GetTextureId(int index) override;
protected:
    
    void DestroyTextureCache();
    int CreateTextureNV12(CVPixelBufferRef buffer);
    int CreateTextureBGRA(CVPixelBufferRef buffer);
    
    CVOpenGLESTextureCacheRef mCVTextureCache;
    CVOpenGLESTextureRef      mCVTexture[2];
};
MK_END
