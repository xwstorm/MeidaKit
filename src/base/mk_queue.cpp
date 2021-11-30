//
//  queue.cpp
//  MediaKit
//
//  Created by xiewei on 2019/6/27.
//

#include "mk_queue.h"


MK_BEGIN

//////////////////////////////////

template <typename T>
LockQueue<T>::LockQueue()
{
    
}

template <typename T>
void LockQueue<T>::enqueue(T t) {
    mLocker.lock();
    addBack(t);
    mLocker.signal();
    mLocker.unlock();
}

template <typename T>
T LockQueue<T>::dequeue(int milliseconds) {
    T t;
    mLocker.lock();
    if (this->empty()) {
        mLocker.wait();
        t = this->popFront();
    }
    mLocker.unlock();
    return t;
}

//////////////////////////////////


//template class MKList<ThreadMessage*>;
MK_END
