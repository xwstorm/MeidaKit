//
//  mk_view.hpp
//  Pods
//
//  Created by xiewei on 2019/11/8.
//

#pragma once
#include "base/mk_base.h"
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface APView : UIView {
}
@end


MK_BEGIN

class MKView {
public:
    MKView();
    ~MKView();
    int updateView(UIView* view);
    CAEAGLLayer* GetLayer();
protected:
    APView* mAPView = nullptr;
    __weak UIView* mUIView = nullptr;
};
MK_END
