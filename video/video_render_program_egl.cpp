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
         "gl_FragColor = vec4(rgb.r, rgb.g, rgb.b, alpha);"
    "}");

const std::string gBGRAFragmentShader = std::string(
                                                    "uniform sampler2D tex;"
                                                    "varying vec2 fragTexCoord;"
                                                    "void main() {"
                                                    "gl_FragColor = texture2D(tex, fragTexCoord);"
                                                    );
BVideoRenderProgramEgl::~BVideoRenderProgramEgl() {
    
}

int BVideoRenderProgramEgl::render(VideoTexture* texture) {
    MKVideoFrameFormat format = texture->GetFormat();
    switch (format) {
        case MK_NV12:
            break;
        case MK_BGRA:
            return renderBGRA(texture);
        default:
            break;
    }
    return S_OK;
}

int BVideoRenderProgramEgl::updateTexture(BVideoFrame* frame) {
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
            return renderBGRA(mTexture);
        case MK_I420:
            return renderI420(mTexture);
        default:
            break;
    }
    
    return S_OK;
}

int BVideoRenderProgramEgl::RenderInternal(VideoTexture* texture) {
    // shader render
//    switch (frame->GetFormat()) {
//        case MK_NV12:
//            return renderNV12(mTexture);
//            break;
//        case MK_NV21:
//            return renderNV12(mTexture);
//        case MK_RGB:
//            return renderRGB(mTexture);
//        case MK_I420:
//            return renderI420(mTexture);
//        default:
//            break;
//    }
    
    return S_OK;
}

int BVideoRenderProgramEgl::renderNV12(VideoTexture* texture) {
    if (mNV12Program == 0) {
        int ret = createNV12Program();
        if (ret != S_OK) {
            return S_FAIL;
        }
    }
    glUseProgram(mNV12Program);
    return S_OK;
}

int BVideoRenderProgramEgl::renderI420(VideoTexture* texture) {
    return S_OK;
}

int BVideoRenderProgramEgl::renderBGRA(VideoTexture* texture) {
    if (mBGRAProgram == 0) {
        int ret = createBGRAProgram();
        if (ret != S_OK) {
            return S_FAIL;
        }
    }
    glUseProgram(mBGRAProgram);
    // render
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    return S_OK;
}


int BVideoRenderProgramEgl::createNV12Program() {
    
    return S_OK;
}

int BVideoRenderProgramEgl::createI420Program() {
    return S_OK;
}

int BVideoRenderProgramEgl::createBGRAProgram() {
    const char* vsSource = gDefaultVertexShader.c_str();
    GLuint vertexShader = GLESUtil::CreateShader(GL_VERTEX_SHADER, &vsSource);
    
    const char* fsSource = gBGRAFragmentShader.c_str();
    GLuint fragmentShader = GLESUtil::CreateShader(GL_FRAGMENT_SHADER, &fsSource);
    
    mBGRAProgram = glCreateProgram();
    if (!mBGRAProgram) {
      return S_FAIL;
    }
    glAttachShader(mBGRAProgram, vertexShader);
    glAttachShader(mBGRAProgram, fragmentShader);
    glLinkProgram(mBGRAProgram);
    GLESUtil::CheckGLESErrorCode();
    
    // create VBO
    mVBO = GLESUtil::CreateDefaultVBO();
    GLESUtil::CheckGLESErrorCode();
    return S_OK;
}


void BVideoRenderProgramEgl::DestroyNV12Program() {
    
}

void BVideoRenderProgramEgl::DestroyI420Program() {
    
}

void BVideoRenderProgramEgl::DestroyBGRAProgram() {
    
}

MK_END
