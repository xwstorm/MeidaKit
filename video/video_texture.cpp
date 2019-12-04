//
//  mk_texture_base.cpp
//  Pods
//
//  Created by xiewei on 2019/11/27.
//

#include "video_texture.h"

MK_BEGIN

VideoTexture::VideoTexture() {
    
}
int VideoTexture::updateFrame(BVideoFrame* frame) {
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

uint32_t VideoTexture::GetTextureId(int index) {
    return 0;
}
MK_END
