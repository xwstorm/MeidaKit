//
//  MKEglRender.mm
//  Pods
//
//  Created by xiewei on 2019/11/26.
//

#import "MKEglRender.h"

#include "video/ios/mk_render_manager_egl.h"
#include "video/ios/mk_view.h"
#include "video/ios/mk_cvpixelbuffer.h"

@interface RenderView : NSObject
- (mk::MKView*)getView;
@end

@interface RenderView() {
    mk::MKView* _mkView;
}
@end

@implementation RenderView
- (instancetype) init {
    self = [super init];
    _mkView = new mk::MKView();
    return self;
}

- (void)dealloc {
    if (_mkView) {
        delete _mkView;
    }
}

- (mk::MKView*)getView {
    return _mkView;
}

- (void)updateView:(UIView*)view {
    if (_mkView) {
        _mkView->updateView(view);
    }
}
@end

@interface MKEglRender() {
    mk::MKEglRenderManager* _eglRender;
    NSMutableDictionary* _viewDict;
}
@end

@implementation MKEglRender

- (instancetype)init {
    self = [super init];
    return self;
}

- (int)open {
    if (_eglRender != nil) {
        return 0;
    }
    _eglRender = new mk::MKEglRenderManager();
    _viewDict = [[NSMutableDictionary alloc] init];
    if (_eglRender->open() == 0) {
        return 0;
    }
    return 0;
}

- (void)close {
    if (_eglRender) {
        _eglRender->close();
    }
    delete _eglRender;
    _eglRender = nil;
}

- (void)setView:(UIView*)view
       toStream:(NSString*)streamId {
    if (!_eglRender) {
        return;
    }
    RenderView* renderView = [_viewDict objectForKey:streamId];
    if (renderView == nil) {
        renderView = [[RenderView alloc] init];
        [_viewDict setValue:renderView forKey:streamId];
    }
    [renderView updateView:view];
    _eglRender->updateView([streamId UTF8String], [renderView getView]);
}

- (void)updateFrame:(CVPixelBufferRef)buffer
       withRotation:(int)roation
           toStream:(NSString*)streamId {
    if (_eglRender) {
        mk::MKCVPixelBuffer* mkbuffer = new mk::MKCVPixelBuffer();
        mkbuffer->updateBuffer(buffer, roation);
        _eglRender->updateFrame([streamId UTF8String], mkbuffer);
    }
}

@end
