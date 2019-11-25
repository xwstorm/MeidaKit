//
//  mk_video_frame.h
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#pragma once

#include "base/mk_base.h"
MK_BEGIN
enum MKVideoFrameType {
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

class MKVideoFrame {
public:
    int width();
    int height();
    MKVideoFrameType format() {
        return mFormat;
    }
    MKVideoRotation rotation() {
        return mRotation;
    }
    int targetWidth();
    int targetHeight();
    void setTargetSize(int width, int height);
protected:
    
    MKVideoFrameType mFormat;
    MKVideoRotation mRotation = MKVideoRotation_0;
    int mTargetWidth = -1;
    int mTargetHeight = -1;
};
MK_END
