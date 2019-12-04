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
    
    if(CheckShaderState(shader) == false){
        assert(false);

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool GLESUtil::CheckGLESErrorCode() {
    int glErrorCode = glGetError();
    if (0!= glErrorCode) {
        assert(false);
        return false;
    }
    return true;
}


unsigned int GLESUtil::CreateDefaultVBO() {
    const float tx = 1.0f;
    const float ty = 1.0f;
    const float vertex[] = {
        //x   y  x    u v
        tx, -ty, 0,   1, 0, // 0
        tx,  ty, 0,   1, 1, // 1
        -tx, ty, 0,   0, 1, // 2

        -tx, ty, 0,   1, 0, // 2
        -tx,-ty, 0,   0, 0, // 3
        tx, -ty, 0,   1, 0, // 0
    };

    GLuint vertexBuffer = 0;
    glGenBuffers(1,&vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*5*6, &vertex[0], GL_STATIC_DRAW);
    return vertexBuffer;
}
MK_END
