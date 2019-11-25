//
//  mk_egl_env.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#include "mk_egl_base.h"
MK_BEGIN
int MKEglBase::open() {
    return S_OK;
}

void MKEglBase::close() {
    
}
int MKEglBase::initContext() {
    return S_OK;
}
void MKEglBase::destroyContext() {
    
}
int MKEglBase::bindView(MKView* view) {
    return S_OK;
}
MK_END
