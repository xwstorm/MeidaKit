//
//  mk_texture_base.hpp
//  Pods
//
//  Created by xiewei on 2019/11/27.
//

#include "base/mk_base.h"
#include "video/mk_video_frame.h"
MK_BEGIN
class MKTextureBase {
public:
    MKTextureBase(MKVideoFrameType format); // format
    virtual int updateFrame(const MKVideoFrame* frame);
    
protected:
    int width = 0;
    int height = 0;
    MKVideoFrameType mFrameType;
};
MK_END
