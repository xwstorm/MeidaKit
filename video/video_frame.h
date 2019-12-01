//
//  video_frame.hpp
//  Pods
//
//  Created by xiewei on 2019/11/27.
//

#pragma once

#include "base/mk_base.h"
MK_BEGIN
enum MKVideoFrameFormat {
    MK_UNKNOW,
    MK_I420,
    MK_NV12,
    MK_NV21,
    MK_RGB,
};

enum MKVideoRotation {
    MKVideoRotation_0,
    MKVideoRotation_90,
    MKVideoRotation_180,
    MKVideoRotation_270
};

enum MKVideoFrameType {
    MK_RAW_FRAME,
    MK_CVPIXEL_FRAME,
};
class BVideoFrame {
public:
    virtual int width() const = 0;
    virtual int height() const = 0;
    MKVideoFrameFormat GetFormat() const {
        return mFormat;
    }
    
    MKVideoRotation rotation() const {
        return mRotation;
    }
    
    int targetWidth() const;
    int targetHeight() const;
    
    MKVideoFrameType GetType();
    
    void setTargetSize(int width, int height);
    
protected:
    
    MKVideoFrameFormat mFormat;
    MKVideoRotation mRotation = MKVideoRotation_0;
    int mTargetWidth = -1;
    int mTargetHeight = -1;
    MKVideoFrameType mType = MK_RAW_FRAME;
};
MK_END

