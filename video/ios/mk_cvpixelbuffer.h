//
//  mk_cvpixelbuffer.h
//  MediaKit
//
//  Created by xiewei on 2019/11/7.
//

#pragma once
#include "base/mk_base.h"
#include "video/mk_video_frame.h"
MK_BEGIN
class MKCVPixelBuffer : public MKVideoFrame {
public:
    int updateBuffer(CVPixelBufferRef buffer);
    
protected:
    CVPixelBufferRef mCVPixelBuffer = nil;
};
MK_END
