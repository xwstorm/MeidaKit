//
//  queue.cpp
//  MediaKit
//
//  Created by xiewei on 2019/6/27.
//

#include "queue.h"


MK_BEGIN

template <typename T>
MKQueue<T>::MKQueue() {
    
}

template <typename T>
void MKQueue<T>::enqueue(T t) {
    mList.addBack(t);
}

template <typename T>
T MKQueue<T>::dequeue() {
    return mList.popFront();
}

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
template <typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template <typename T>
void PriorityQueue<T>::enqueue(T t, Priority priority) {
    mLocker.lock();
    switch (priority) {
        case LOW_PRIORITY:
            this->addBack(t);
            break;
        case HIGHT_PRIORITY:
            mList.addBack(t);
        default:
            break;
    }
    mLocker.signal();
    mLocker.unlock();
}

template <typename T>
T PriorityQueue<T>::dequeue(int milliseconds) {
    T t;
    mLocker.lock();
    if (!mList.empty()) {
        t = mList.popFront();
    } else if (this->empty()) {
        mLocker.wait();
        t = this->popFront();
    } else {
        t = this->popFront();
    }
    mLocker.unlock();
    return t;
}

template <typename T>
bool PriorityQueue<T>::start() {
    return true;
}
template <typename T>
void PriorityQueue<T>::stop() {
    
}



class ThreadMessage;
template class PriorityQueue<ThreadMessage*>;

//template class MKList<ThreadMessage*>;
MK_END
