//
//  mk_egl_base.h
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#pragma once
#include "base/mk_base.h"
MK_BEGIN
class MKView;
class MKEglBase {
public:
    int open();
    void close();
    int bindView(MKView* view);
    
protected:
    int initContext();
    void destroyContext();
    
protected:
    MKView* mLastView = nullptr;
};

MK_END
