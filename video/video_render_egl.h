//
//  video_render_egl.h
//  MediaKit
//
//  Created by xiewei on 2019/11/4.
//

#pragma once
#include <map>
#include "video/video_render_base.h"
#include "video/mk_egl_base.h"
#include "video/mk_view.h"

MK_BEGIN


class RenderResource {
public:
    inline void updateFrame(MKVideoFrame* frame) {
        mFrame = frame;
        if(frame) {
            mDirty = true;
        } else {
            mDirty = false;
        }
    }
    inline void updateView(MKView* view) {
        mView = view;
    }
    
    inline MKView* view() {
        return mView;
    }
    inline MKVideoFrame* frame() {
        return mFrame;
    }
    inline bool dirty() {
        return mDirty;
    }
    void resetDirty() {
        mDirty = false;
    }
protected:
    MKVideoFrame* mFrame = nullptr;
    MKView* mView = nullptr;
    bool mDirty = false;
};

class VideoRenderEGL : public VideoRenderBase {
public:
    VideoRenderEGL();
    int open() override;
    void close() override;
    int updateFrame(std::string streamId, MKVideoFrame* videoFrame) override;
    int updateView(std::string streamId, MKView*);
    void setRenderInterval(int interval);
protected:
    virtual void render();
    void postDelayTask();
protected:
    MKEglBase mEglBase;
    std::mutex mMapMutex;
    std::atomic_int mRenderInterval; // ms
    std::map<std::string, RenderResource> mResourceMap;
    std::chrono::system_clock::time_point mLastRenderTime;
};

MK_END
