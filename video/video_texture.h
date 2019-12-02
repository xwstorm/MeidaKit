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
class VideoTexture {
public:
    VideoTexture(); // format
    virtual int updateFrame(const BVideoFrame* frame);
    virtual uint32_t GetTextureId(int index);
protected:
    int width = 0;
    int height = 0;
    MKVideoFrameFormat mFrameType;
};
MK_END
