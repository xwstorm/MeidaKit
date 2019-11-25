//
//  mk_video_buffer.cpp
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#include "mk_video_frame.h"
MK_BEGIN
int MKVideoFrame::width() {
    return 0;
}

int MKVideoFrame::height() {
    return 0;
}


int MKVideoFrame::targetWidth() {
    if (mTargetWidth == -1) {
        return width();
    }
    return mTargetWidth;
}

int MKVideoFrame::targetHeight() {
    if (mTargetHeight == -1) {
        return height();
    }
    return mTargetHeight;
}

void MKVideoFrame::setTargetSize(int width, int height) {
    mTargetWidth = width;
    mTargetHeight = height;
}
MK_END
