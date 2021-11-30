//
//  priority_queue.hpp
//  MediaKit
//
//  Created by xiewei on 2019/10/25.
//


#pragma once

#include <mutex>
#include <condition_variable>
#include "mk_list.h"

MK_BEGIN

template <typename T>
class PriorityQueue {
public:
    enum Priority {
        LOW_PRIORITY,
        HIGHT_PRIORITY,
    };
    
    PriorityQueue();
    void enqueue(T t, Priority priority = LOW_PRIORITY);
    T dequeue(int milliseconds = kForever);
    bool start();
    void stop();
protected:

    void lock() {
        std::unique_lock<std::mutex> uLock(mMutex);
        mCV.wait(uLock);
    }
    void unLock() {
        mCV.notify_one();
    }
protected:
    MKList<T> mHighList;
    MKList<T> mLowList;
    
    std::mutex mMutex;
    std::condition_variable mCV;
    
    const int mLockVar = 0;
    const int mUnlockVar = 1;
    std::atomic_int mSpinMutex;
};


template <typename T>
PriorityQueue<T>::PriorityQueue()
: mSpinMutex(1)
{
}

template <typename T>
void PriorityQueue<T>::enqueue(T t, Priority priority) {
    std::unique_lock<std::mutex> uLock(mMutex);
    switch (priority) {
        case LOW_PRIORITY:
            mLowList.addBack(t);
            break;
        case HIGHT_PRIORITY:
            mHighList.addBack(t);
        default:
            break;
    }
    mCV.notify_one();
}

template <typename T>
T PriorityQueue<T>::dequeue(int milliseconds) {
    T t;
    std::unique_lock<std::mutex> uLock(mMutex);
    while (mHighList.empty() && mLowList.empty()) {
        if (milliseconds == kForever) {
            mCV.wait(uLock);
        } else if (milliseconds > 0) {
            // wait until
            mCV.wait_for(uLock, std::chrono::milliseconds(milliseconds));
        }
        if (!mHighList.empty()) {
            t = mHighList.popFront();
            break;
        } else if (!mLowList.empty()) {
            t = mLowList.popFront();
            break;
        } else {
            if (milliseconds != kForever) {
                break;
            }
        }
    }
    return t;
}

template <typename T>
bool PriorityQueue<T>::start() {
    return true;
}
template <typename T>
void PriorityQueue<T>::stop() {
    
}

MK_END
