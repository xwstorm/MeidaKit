//
//  queue.hpp
//  MediaKit
//
//  Created by xiewei on 2019/6/27.
//

#pragma once

#include <stdio.h>
#include "mk_list.h"

MK_BEGIN
template <typename T>
class MKQueue : public MKList<T> {
public:
    MKQueue();
    void enqueue(T t);
    T dequeue();
protected:
    MKList<T> mList;
};

class Locker {
public:
    Locker():mWaiting(0){};
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

template <typename T>
class LockQueue : public MKList<T> {
public:
    LockQueue();
    void enqueue(T t);
    T dequeue(int milliseconds);
protected:
    Locker mLocker;
};


template <typename T>
class PriorityQueue : public MKList<T> {
public:
    enum Priority {
        LOW_PRIORITY,
        HIGHT_PRIORITY,
    };
    
    PriorityQueue();
    void enqueue(T t, Priority priority = LOW_PRIORITY);
    T dequeue(int milliseconds);
protected:
    Locker mLocker;
    MKList<T> mList;
};

MK_END
