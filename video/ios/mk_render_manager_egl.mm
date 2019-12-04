//
//  video_render_egl_ios.cpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#include "mk_render_manager_egl.h"
#include "mk_egl_env.h"
#include "mk_cvpixelbuffer.h"
#include "mk_video_render_program_egl.h"
#include "mk_video_render_egl.h"
MK_BEGIN

MKEglRenderManager::MKEglRenderManager() {
    mEGLEnv = new MKEglEnv();
}

MKEglRenderManager::~MKEglRenderManager() {
    if (mEGLEnv) {
        delete mEGLEnv;
    }
}

int MKEglRenderManager::updateFrame(std::string streamId, CVPixelBufferRef videoFrame) {
    
    return S_OK;
}

int MKEglRenderManager::updateFrame(std::string streamId, BVideoFrame* videoFrame) {
    return BRenderManagerEgl::updateFrame(streamId, videoFrame);
}

VideoRenderEgl* MKEglRenderManager::CreateVideoRender() {
    VideoRenderEgl* eglRender = new MKVideoRenderEgl();
    if (mEGLEnv) {
        eglRender->SetEglContext(mEGLEnv->GetEglContext());
    }
    return eglRender;
}
MK_END
