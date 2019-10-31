//
//  mediakit_manager.cpp
//  Pods
//
//  Created by xiewei on 2019/7/1.
//

#include "mediakit_manager.h"
MK_BEGIN
MediaKitManager::MediaKitManager() {
    
}

int MediaKitManager::init() {
    if (mLooper == nullptr) {
        mLooper = new MKThread("looper");
    }
    mLooper->open();
    mLooper->start();
    return 0;
}
MK_END
