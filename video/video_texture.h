//
//  video_texture.h
//  Pods
//
//  Created by xiewei on 2019/11/27.
//
#pragma once

#include "base/mk_base.h"
#include "video/video_frame.h"
MK_BEGIN
class MKEglContext;
class VideoTexture {
public:
    VideoTexture(); // format
    virtual int updateFrame(BVideoFrame* frame);
    virtual uint32_t GetTextureId(int index);
    void SetEglContext(MKEglContext* context) { mEglContext = context;}
    
    MKVideoFrameFormat GetFormat() const {
        return mFrameType;
    }
    
protected:
    int width = 0;
    int height = 0;
    MKVideoFrameFormat mFrameType;
    MKEglContext* mEglContext = nullptr;
};
MK_END
