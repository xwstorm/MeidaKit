//
//  mk_egl_ios.cpp
//  Pods
//
//  Created by xiewei on 2019/11/26.
//

#include "video/ios/mk_egl_env.h"
#include "mk_egl_context.h"
#include "mk_view.h"

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
MK_BEGIN


MKEglEnv::~MKEglEnv() {
    
}

int MKEglEnv::open(MKEglContext* sharedContext) {
    if (mInitialized) {
        return S_OK;
    }

    if (initContext(sharedContext) != S_OK) {
        assert(false);
        close();
        return S_FAIL;
    }
    
    if (SetupRenderBuffer() != S_OK) {
        assert(false);
        close();
        return S_FAIL;
    }
    
    mInitialized = true;
    
    return S_OK;
}

void MKEglEnv::close() {
    DestroyRenderBuffer();
    DestroyContext();
    mGLContext = nil;
}

int MKEglEnv::initContext(MKEglContext* sharedContext) {
    assert(mGLContext == nullptr);
    if (sharedContext == nullptr) {
        mGLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    } else {
        mGLContext = [[EAGLContext alloc] initWithAPI:[sharedContext->glContext API] sharegroup:[sharedContext->glContext sharegroup]];
    }
    if (![EAGLContext setCurrentContext:mGLContext]) {
        assert(false);
        close();
        return S_FAIL;
    }
    return S_OK;
}

void MKEglEnv::DestroyContext() {
    [EAGLContext setCurrentContext:nil];
}

int MKEglEnv::SetupRenderBuffer() {
    if (mColorBuffer == 0) {
        glGenRenderbuffers(1, &mColorBuffer);
    }
    if (mFrameBuffer == 0) {
        glGenFramebuffers(1, &mFrameBuffer);
    }
    return S_OK;
}

void MKEglEnv::DestroyRenderBuffer() {
    glFinish();
    if(mColorBuffer != 0) {
        glDeleteRenderbuffers(1, &mColorBuffer);
        mColorBuffer = 0;
    }
    if(mFrameBuffer !=0 ) {
        glDeleteFramebuffers(1, &mFrameBuffer);
        mFrameBuffer = 0;
    }
}

int MKEglEnv::bindView(MKView* view) {
    if (!mInitialized) {
        assert(false);
        return S_FAIL;
    }
    CAEAGLLayer* eglLayer = view->GetLayer();
    if (view && eglLayer) {
        if (mLastEglLayer != eglLayer) {

            glBindRenderbuffer(GL_RENDERBUFFER, mColorBuffer);
            [mGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:eglLayer];

            glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorBuffer);
            
            mLastEglLayer = eglLayer;
        }
    } else {
        [mGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:nil];
    }
    return S_OK;
}
MK_END
