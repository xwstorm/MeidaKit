//
//  mk_cv_texture.cpp
//  Pods
//
//  Created by xiewei on 2019/11/28.
//

#include "mk_cv_texture.h"
#include "video/video_frame.h"
#include "mk_cvpixelbuffer.h"
#include "mk_egl_context.h"

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

MK_BEGIN

MKCVTexture::~MKCVTexture() {
    DestroyTextureCache();
}

int MKCVTexture::updateFrame(CVPixelBufferRef buffer) {
    return S_OK;
}

int MKCVTexture::updateFrame(BVideoFrame* frame) {
    if (frame->GetType() != MK_CVPIXEL_FRAME) {
        return S_FAIL;
    }
    DestroyTextureCache();
    
    MKCVPixelBuffer* cvbuffer = static_cast<MKCVPixelBuffer*>(frame);
    CVPixelBufferRef buffer = cvbuffer->GetCVPixelBuffer();
    MKVideoFrameFormat format = frame->GetFormat();
    mFrameType = format;
    switch (format) {
        case MK_NV12:
            return CreateTextureNV12(buffer);
            break;
        case MK_I420:
            break;
        case MK_BGRA:
            return CreateTextureBGRA(buffer);
            break;
            
            
        default:
            break;
    }
    return S_OK;
}

int MKCVTexture::CreateTextureNV12(CVPixelBufferRef buffer) {
    CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, mEglContext->glContext, NULL, &mCVTextureCache);
    if (err != noErr) {
        assert(false);
        return S_FAIL;
    }
    
    GLsizei frame_width  = (GLsizei)CVPixelBufferGetWidth(buffer);
    GLsizei frame_height = (GLsizei)CVPixelBufferGetHeight(buffer);

    GLsizei width[]  = {frame_width, frame_width / 2};
    GLsizei height[] = {frame_height, frame_height / 2};
    GLint format[] = {GL_RED_EXT, GL_RG_EXT};
    for (int i=0; i<2; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                           mCVTextureCache,
                                                           buffer,
                                                           NULL,
                                                           GL_TEXTURE_2D,
                                                           format[i],
                                                           width[i],
                                                           height[i],
                                                           format[i],
                                                           GL_UNSIGNED_BYTE,
                                                           i,
                                                           &mCVTexture[i]);
        if (err != noErr) {
            assert(false);
            return S_FAIL;
        }
    }
    
    return S_OK;
}
int MKCVTexture::CreateTextureBGRA(CVPixelBufferRef buffer) {
    CVReturn err = CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, mEglContext->glContext, NULL, &mCVTextureCache);
    if (err != noErr) {
        assert(false);
        return S_FAIL;
    }
    
    GLsizei frame_width  = (GLsizei)CVPixelBufferGetWidth(buffer);
    GLsizei frame_height = (GLsizei)CVPixelBufferGetHeight(buffer);

    err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                       mCVTextureCache,
                                                       buffer,
                                                       NULL,
                                                       GL_TEXTURE_2D,
                                                       GL_RGBA,
                                                       frame_width,
                                                       frame_height,
                                                       GL_BGRA,
                                                       GL_UNSIGNED_BYTE,
                                                       0,
                                                       &mCVTexture[0]);
    if (err != noErr) {
        assert(false);
        return S_FAIL;
    }

//    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    return S_OK;
}

uint32_t MKCVTexture::GetTextureId(int index) {
    return 0;
}

void MKCVTexture::DestroyTextureCache() {
    for (int i=0; i<2; ++i) {
        if (mCVTexture[i]) {
            CFRelease(mCVTexture[i]);
            mCVTexture[i] = NULL;
        }
    }
    
    if (mCVTextureCache) {
#if defined(MK_IOS)
        CVOpenGLESTextureCacheFlush(mCVTextureCache, 0);
#else
        CVOpenGLTextureCacheFlush(mCVTextureCache, 0);
#endif
        CFRelease(mCVTextureCache);
        mCVTextureCache = NULL;
    }
}
MK_END
