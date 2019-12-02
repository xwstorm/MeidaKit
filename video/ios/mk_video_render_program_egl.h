//
//  mk_video_render_program_egl.h
//  Pods
//
//  Created by xiewei on 2019/12/1.
//

#pragma once
#include "video/video_render_program_egl.h"
#include "mk_cv_texture.h"
MK_BEGIN
class MKVideoRenderProgramEgl : public BVideoRenderProgramEgl {
public:
    ~MKVideoRenderProgramEgl(){};
protected:
    int updateTexture(BVideoFrame* frame) override;
    
    MKCVTexture mCVTexture;
};
MK_END
