//
//  mk_plock.hpp
//  Pods
//
//  Created by xiewei on 2019/10/31.
//

#pragma once

#include "base/mk_base.h"
#include <pthread.h>

MK_BEGIN

class MKPLocke {
public:
    MKPLocke(): mWaiting(0){};
    void lock() {   pthread_mutex_lock(&mMutex);}
    void unlock() { pthread_mutex_unlock(&mMutex);}
    void signal() {
        if (mWaiting) {
            pthread_cond_signal(&mCond);
        }
    }
    void wait() {
        mWaiting++;
        pthread_cond_wait(&mCond, &mMutex);
        mWaiting--;
    }
    
protected:
    unsigned int mWaiting;
    pthread_mutex_t mMutex;
    pthread_cond_t mCond;
};
MK_END
