//
//  mk_video_frame.h
//  MediaKit
//
//  Created by xiewei on 2019/11/6.
//

#pragma once

#include "video_frame.h"

MK_BEGIN
class MKVideoFrame : public BVideoFrame {
public:
    MKVideoFrame();
    
protected:
    int mWidth = 0;
    int mHeight = 0;
    char* mData = nullptr;
};
MK_END
