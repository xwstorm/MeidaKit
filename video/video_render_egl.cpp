//
//  video_render_egl.cpp
//  Pods
//
//  Created by xiewei on 2019/12/2.
//

#include "video_render_egl.h"
MK_BEGIN

int VideoRenderEgl::Render() {
    VideoTexture* texture = GetFrameTexture();
    if (texture) {
        return RenderTexture(texture);
    }
    return S_FAIL;
}

VideoTexture* VideoRenderEgl::GetFrameTexture() {
    return nullptr;
}

int VideoRenderEgl::RenderTexture(VideoTexture* texture) {
    if (mRenderProgram) {
        mRenderProgram->render(texture);
    }
    return S_OK;
}

MK_END
