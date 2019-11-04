//
//  mediakit_manager.hpp
//  Pods
//
//  Created by xiewei on 2019/7/1.
//

#pragma

#include <stdio.h>
#include "base/mk_thread.h"
MK_BEGIN
class MediaKitManager {
public:
    MediaKitManager();
    int init();
protected:
    MKThread* mLooper;
    MKThread* mRenderThread;
};
MK_END
