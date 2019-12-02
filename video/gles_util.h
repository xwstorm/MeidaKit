//
//  gles_util.h
//  Pods
//
//  Created by xiewei on 2019/11/29.
//

#pragma once
#include "base/mk_base.h"

#if defined(MK_IOS)
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

MK_BEGIN

class GLESUtil {
public:
    uint32_t CreateShader(uint32_t shaderType, const char** shaderSource);
    bool CheckShaderState(int obj);
};

MK_END
