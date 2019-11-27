//
//  mk_texture_base.cpp
//  Pods
//
//  Created by xiewei on 2019/11/27.
//

#include "mk_texture_base.h"

MK_BEGIN

MKTextureBase::MKTextureBase(MKVideoFrameType format)
    : mFrameType(format){
    
}
int MKTextureBase::updateFrame(const MKVideoFrame* frame) {
    assert(mFrameType == frame->GetFormat());
    return S_OK;
}
MK_END
