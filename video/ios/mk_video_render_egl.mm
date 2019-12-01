//
//  video_render_egl_ios.cpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#include "mk_video_render_egl.h"
#include "mk_egl_env.h"
MK_BEGIN

MKVideoRenderEgl::MKVideoRenderEgl() {
    mEGLEnv = new MKEglEnv();
}

MKVideoRenderEgl::~MKVideoRenderEgl() {
    if (mEGLEnv) {
        delete mEGLEnv;
    }
}

int MKVideoRenderEgl::updateFrame(std::string streamId, BVideoFrame* videoFrame) {
    if (videoFrame->GetType() == MK_CVPIXEL_FRAME) {
        // update to texture
    }
    
    return S_OK;
}

int MKVideoRenderEgl::updateFrame(std::string streamId, CVPixelBufferRef videoFrame) {
    
    return S_OK;
}

MK_END
