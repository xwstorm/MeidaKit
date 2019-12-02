//
//  mk_cvpixelbuffer.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/7.
//

#include "mk_cvpixelbuffer.h"

MK_BEGIN
MKCVPixelBuffer::MKCVPixelBuffer() {
    mType = MK_CVPIXEL_FRAME;
}

void MKCVPixelBuffer::Release() {
    if (mCVPixelBuffer) {
        CVPixelBufferRelease(mCVPixelBuffer);
    }
    BVideoFrame::Release();
}

int MKCVPixelBuffer::updateBuffer(CVPixelBufferRef buffer, int rotation) {
    if (mCVPixelBuffer) {
        CVPixelBufferRelease(mCVPixelBuffer);
    }
    mCVPixelBuffer = CVPixelBufferRetain(buffer);
//    mRotation = 0;
    return S_OK;
}

int MKCVPixelBuffer::width() const {
    if (mCVPixelBuffer) {
        return (int)CVPixelBufferGetWidth(mCVPixelBuffer);
    } else {
        return 0;
    }
}

int MKCVPixelBuffer::height() const {
    if (mCVPixelBuffer) {
        return (int)CVPixelBufferGetHeight(mCVPixelBuffer);
    } else {
        return 0;
    }
}

MK_END
