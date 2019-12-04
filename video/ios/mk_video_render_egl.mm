//
//  mk_video_render_egl.cpp
//  Pods
//
//  Created by xiewei on 2019/12/2.
//

#include "mk_video_render_egl.h"
#include "mk_cvpixelbuffer.h"
MK_BEGIN

VideoTexture* MKVideoRenderEgl::GetFrameTexture() {
    mCVTexture.SetEglContext(mEglContext);
    int ret = mCVTexture.updateFrame(mFrame);
    if (ret == S_OK) {
        return &mCVTexture;
    } else {
        return VideoRenderEgl::GetFrameTexture();
    }
}
MK_END
