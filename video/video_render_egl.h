//
//  video_render_egl.h
//  Pods
//
//  Created by xiewei on 2019/12/2.
//

#pragma once
#include "video_render_program_egl.h"

MK_BEGIN
class BVideoFrame;
class MKView;
class VideoRenderEgl {
public:
    int Render();
    inline void updateFrame(BVideoFrame* frame) {
        mFrame = frame;
        if(frame) {
            mDirty = true;
        } else {
            mDirty = false;
        }
    }
    
    inline void updateView(MKView* view) {
        if (mView) {
            delete mView;
        }
        mView = view;
    }
    
    inline MKView* view() {
        return mView;
    }
    inline BVideoFrame* frame() {
        return mFrame;
    }
    inline bool dirty() {
        return mDirty;
    }
    void resetDirty() {
        mDirty = false;
    }
    
protected:
    int RenderTexture(VideoTexture* texture);
public:
    BVideoRenderProgramEgl* mRenderer = nullptr;
    VideoTexture mTexture;
    
    BVideoFrame* mFrame = nullptr;
    MKView* mView = nullptr;
    bool mDirty = false;
};
MK_END

