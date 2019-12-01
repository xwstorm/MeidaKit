//
//  mk_texture_base.cpp
//  Pods
//
//  Created by xiewei on 2019/11/27.
//

#include "video_texture.h"

MK_BEGIN

VideoTexture::VideoTexture(MKVideoFrameFormat format)
    : mFrameType(format){
    
}
int VideoTexture::updateFrame(const BVideoFrame* frame) {
    assert(mFrameType == frame->GetFormat());
    switch (mFrameType) {
        case MK_I420: {
            break;
        }
        case MK_NV12: {
            break;
        }
        case MK_NV21: {
            break;
        }
        case MK_RGB: {
            break;
        }
        default:
            break;
    }
    return S_OK;
}
MK_END
