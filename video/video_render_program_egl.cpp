//
//  mk_video_renderer.cpp
//  Pods
//
//  Created by xiewei on 2019/11/28.
//

#include <string>
#include "video_render_program_egl.h"
#include "video/egl_env.h"
#include "video/gles_util.h"

MK_BEGIN
const std::string gDefaultVertexShader = std::string(
    "attribute vec3 vert;"
    "attribute vec2 vertTexCoord;"
    "varying vec2 fragTexCoord;"
    "void main() {"
         "fragTexCoord = vertTexCoord;"
         "gl_Position = vec4(vert,1);"
    "}");

const std::string gNV12ToRGBFragmentShader = std::string(
    "uniform sampler2D tex_y;"
    "uniform sampler2D tex_uv;"
    "varying vec2 fragTexCoord;"
    "void main() {"
         "vec3 yuv;"
         "yuv.x = texture2D(tex_y, fragTexCoord).r;"
         "yuv.y = texture2D(tex_uv, fragTexCoord).a;"
         "yuv.z = texture2D(tex_uv, fragTexCoord).r;"
         "float alpha = 1.0;"
         "vec3 rgb;"
         "yuv.y = yuv.y - 0.5;"
         "yuv.z = yuv.z - 0.5;"
         "rgb = mat3( 1.0,       1.0,         1.0,"
         "0.0,       -0.343,  1.765,"
         "1.4,  -0.711,  0.0)  * yuv;"
    "}");

int BVideoRenderer::render(BVideoFrame* frame) {
    return S_OK;
}

int BVideoRenderer::updateTexture(BVideoFrame* frame) {
    // update texture
    if (mTexture->updateFrame(frame) != S_OK) {
        return S_FAIL;
    }
    
    // shader render
    switch (frame->GetFormat()) {
        case MK_NV12:
            return renderNV12(mTexture);
            break;
        case MK_NV21:
            return renderNV12(mTexture);
        case MK_RGB:
            return renderRGB(mTexture);
        case MK_I420:
            return renderI420(mTexture);
        default:
            break;
    }
    
    return S_OK;
}

int BVideoRenderer::renderNV12(VideoTexture* texture) {
    if (mNV12Program == 0) {
        int ret = createNV12Program();
        if (ret != S_OK) {
            return S_FAIL;
        }
    }
    glUseProgram(mNV12Program);
    return S_OK;
}

int BVideoRenderer::renderI420(VideoTexture* texture) {
    return S_OK;
}

int BVideoRenderer::renderRGB(VideoTexture* texture) {
    return S_OK;
}


int BVideoRenderer::createNV12Program() {
    
    return S_OK;
}
int BVideoRenderer::createI420Program() {
    return S_OK;
}
int BVideoRenderer::createRGBProgram() {
    return S_OK;
}


void BVideoRenderer::DestroyNV12Program() {
    
}

void BVideoRenderer::DestroyI420Program() {
    
}

void BVideoRenderer::DestroyRGBProgram() {
    
}

MK_END
