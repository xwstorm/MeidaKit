//
//  event.cpp
//  MediaKit
//
//  Created by xiewei on 2019/6/26.
//

#include "event.h"
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

Event::Event() {
    pthread_mutex_init(&mMutex, nullptr);
    pthread_cond_init(&mCond, nullptr);
}
Event::~Event() {
    pthread_mutex_destroy(&mMutex);
    pthread_cond_destroy(&mCond);
}
void Event::signal() {
    pthread_mutex_lock(&mMutex);
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mMutex);
}
void Event::reSet() {
    pthread_mutex_lock(&mMutex);
    
    pthread_mutex_unlock(&mMutex);
}
bool Event::wait(int milliseconds) {
    int error = 0;
    struct timespec ts;
    if (milliseconds != kForever) {
        
    }
    pthread_mutex_lock(&mMutex);
    if (milliseconds != kForever) {
        error = pthread_cond_timedwait(&mCond, &mMutex, &ts);
    } else {
        error = pthread_cond_wait(&mCond, &mMutex);
    }
    return (error == 0);
}
