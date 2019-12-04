//
//  mk_video_render_egl.h
//  Pods
//
//  Created by xiewei on 2019/12/2.
//

#include "video/video_render_egl.h"
#include "mk_cv_texture.h"

MK_BEGIN
class MKVideoRenderEgl : public VideoRenderEgl {
protected:
    VideoTexture* GetFrameTexture() override;
    
protected:
    MKCVTexture mCVTexture;
};
MK_END
