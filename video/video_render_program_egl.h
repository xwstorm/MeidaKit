//
//  video_render_program_egl.hpp
//  Pods
//
//  Created by xiewei on 2019/11/28.
//

#pragma once

#include "base/mk_base.h"
#include "video_texture.h"

MK_BEGIN
class BVideoFrame;
class BVideoRenderProgramEgl {
public:
    virtual ~BVideoRenderProgramEgl();
    
    int render(BVideoFrame* frame);
    
protected:
    virtual int updateTexture(BVideoFrame* frame);
    
    int RenderInternal(VideoTexture*);
    
    int renderNV12(VideoTexture* texture);
    int renderI420(VideoTexture* texture);
    int renderRGB(VideoTexture* texture);
    
    int createNV12Program();
    int createI420Program();
    int createRGBProgram();
    
    void DestroyNV12Program();
    void DestroyI420Program();
    void DestroyRGBProgram();
    
protected:
    VideoTexture* mTexture = nullptr;
    uint32_t mNV12Program = 0;
    uint32_t mNV21Program = 0;
    uint32_t mI420Program = 0;
    uint32_t mRGBProgram = 0;
};
MK_END
