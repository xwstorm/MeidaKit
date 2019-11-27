//
//  video_render_egl_ios.cpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#include "video_render_egl.h"
#include "mk_egl_env.h"
MK_BEGIN
VideoRenderEgl::VideoRenderEgl() {
    mEGLEnv = new MKEglEnv();
}


VideoRenderEgl::~VideoRenderEgl() {
    if (mEGLEnv) {
        delete mEGLEnv;
    }
}
MK_END
