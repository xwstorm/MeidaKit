//
//  event.hpp
//  MediaKit
//
//  Created by xiewei on 2019/6/26.
//

#pragma once
#include <stdio.h>

#include <pthread.h>

class Event {
public:
    static const int kForever = -1;
    Event();
    ~Event();
    void signal();
    void reSet();
    bool wait(int milliseconds);
    
private:
    pthread_mutex_t mMutex;
    pthread_cond_t mCond;
};
