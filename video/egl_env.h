//
//  egl_env.h
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#pragma once
#include "base/mk_base.h"
MK_BEGIN
class MKView;
class MKEglContext;
class BEglEnv {
public:
    virtual int open(MKEglContext* sharedContext) = 0;
    virtual void close() = 0;
    virtual int bindView(MKView* view) = 0;
    virtual ~BEglEnv() {};
    MKEglContext* GetEglContext() { return mEglContext;}
    
protected:
    bool mInitialized = false;
    MKEglContext* mEglContext = nullptr;
};

MK_END
