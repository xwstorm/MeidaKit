//
//  mk_egl_env.h
//  Pods
//
//  Created by xiewei on 2019/11/26.
//

#pragma once
#include "base/mk_base.h"
#include "video/egl_env.h"
#include "mk_egl_context.h"

MK_BEGIN
class MKEglEnv : public BEglEnv{
public:
    ~MKEglEnv();
    int open(MKEglContext* sharedContext) override;
    void close() override;
    int bindView(MKView* view) override;
protected:
    int initContext(MKEglContext* sharedContext);
    void DestroyContext();
    
    int SetupRenderBuffer();
    void DestroyRenderBuffer();
    
protected:
    // android EGLContext, this is a pointer
    EAGLContext* mGLContext = nullptr;
    __weak CAEAGLLayer* mLastEglLayer = nil; // should put into MKView
    
    uint32_t mColorBuffer = 0;
    uint32_t mFrameBuffer = 0;
};

MK_END
