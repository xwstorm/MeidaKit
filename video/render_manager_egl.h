//
//  render_manager_egl.h
//  MediaKit
//
//  Created by xiewei on 2019/11/4.
//

#pragma once
#include <map>
#include "video/render_manager_base.h"
#include "video/egl_env.h"
#include "video_texture.h"
#include "video_render_egl.h"

MK_BEGIN
class MKView;

class BRenderManagerEgl : public BVideoRender {
public:
    BRenderManagerEgl();
    int open() override;
    void close() override;
    int updateFrame(std::string streamId, BVideoFrame* videoFrame) override;
    int updateView(std::string streamId, MKView* view);
    void setRenderInterval(int interval);
    
//    virtual VideoTexture* GetValidTexture(BVideoFrame);
    
protected:
    virtual void render();
    void postDelayTask();
protected:
    BEglEnv* mEGLEnv = nullptr;
    std::mutex mMapMutex;
    std::atomic_int mRenderInterval; // ms
    std::map<std::string, VideoRenderEgl*> mResourceMap;
    std::chrono::system_clock::time_point mLastRenderTime;
};

MK_END
