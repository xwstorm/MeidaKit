//
//  gles_util.cpp
//  Pods
//
//  Created by xiewei on 2019/11/29.
//

#include "gles_util.h"
MK_BEGIN

bool GLESUtil::CheckShaderState(int obj) {
    GLint status = GL_FALSE;
    if( glIsShader(obj))
        glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
    if( glIsProgram(obj))
        glGetProgramiv(obj, GL_LINK_STATUS, &status);
    if(status == GL_TRUE)
        return true;
    const GLint tLen = 1024;
    GLint len = tLen;
    char log[tLen];
    if(glIsShader(obj)) {
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&len);
        glGetShaderInfoLog(obj, len, NULL, log);
    }
    if(glIsProgram(obj)) {
        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len);
        glGetProgramInfoLog(obj, len, NULL, log);
    }
    assert(false);
    return false;
}

uint32_t GLESUtil::CreateShader(uint32_t shaderType, const char** shaderSource) {
    uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, shaderSource, nullptr);
    
    glCompileShader(shader);
    
    if(checkShaderState(shader) == false){
        assert(false);

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
MK_END
