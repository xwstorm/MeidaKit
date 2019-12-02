//
//  mk_video_render_program_egl.cpp
//  Pods
//
//  Created by xiewei on 2019/12/1.
//

#include "mk_video_render_program_egl.h"
#include "mk_cvpixelbuffer.h"
MK_BEGIN

int MKVideoRenderProgramEgl::updateTexture(BVideoFrame* videoFrame) {
    if (videoFrame->GetType() == MK_CVPIXEL_FRAME) {
        // update to texture
        MKCVPixelBuffer* pixelBuffer = static_cast<MKCVPixelBuffer*>(videoFrame);
        CVPixelBufferRef buffer = pixelBuffer->GetCVPixelBuffer();
        int ret = mCVTexture.updateFrame(buffer);
        if (ret == S_FAIL) {
            return BVideoRenderProgramEgl::updateTexture(videoFrame);
        }
    } else {
        return BVideoRenderProgramEgl::updateTexture(videoFrame);
    }
    return S_OK;
}
MK_END
