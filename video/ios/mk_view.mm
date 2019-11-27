//
//  mk_view.cpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#include "mk_view.h"
@implementation APView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    self.layer.contentsScale = [UIScreen mainScreen].scale;
    
    return self;
}
@end

MK_BEGIN

MKView::MKView() {
}

MKView::~MKView() {
    
}

int MKView::updateView(UIView* view) {
    [mAPView removeFromSuperview];
    if (view) {
        mAPView = [[APView alloc] init];
        mAPView.frame = CGRectMake(0, 0, view.frame.size.width, view.frame.size.height);
        mAPView.center = CGPointMake(view.frame.size.width/2, view.frame.size.height/2);
    } else {
        mAPView = nil;
    }
    return S_OK;
}

CAEAGLLayer* MKView::GetLayer() {
    if (mAPView) {
        return (CAEAGLLayer *)mAPView.layer;
    } else {
        return nullptr;
    }
}
MK_END
