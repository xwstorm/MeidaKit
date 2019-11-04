//
//  mk_lock.h
//  Pods
//
//  Created by xiewei on 2019/10/31.
//
#pragma once
#include <mutex>
#include "base/mk_base.h"
MK_BEGIN
class MKLock {
public:
    void notifyOne() {
        mCV.notify_one();
    }
    void notifyAll() {
        mCV.notify_all();
    }
    void wait() {
        std::unique_lock<std::mutex> lock(mMutex);
        mCV.wait(lock);
    }
    
    bool waitFor(int millisecond) {
        std::unique_lock<std::mutex> lock(mMutex);
        std::cv_status status = mCV.wait_for(lock, std::chrono::milliseconds(millisecond));
        bool ret = status == std::cv_status::no_timeout ? true : false;
        return ret;
    }
    
protected:
    std::mutex mMutex;
    std::condition_variable mCV;
};
MK_END
