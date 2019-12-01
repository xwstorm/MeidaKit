//
//  mk_cvpixelbuffer.h
//  MediaKit
//
//  Created by xiewei on 2019/11/7.
//

#pragma once
#include "base/mk_base.h"
#include "video/video_frame.h"
MK_BEGIN
class MKCVPixelBuffer : public BVideoFrame {
public:
    MKCVPixelBuffer();
    int updateBuffer(CVPixelBufferRef buffer);
    
    int width() const override;
    int height() const override;
protected:
    CVPixelBufferRef mCVPixelBuffer = nil;
};
MK_END
