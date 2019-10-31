//
//  queue.hpp
//  MediaKit
//
//  Created by xiewei on 2019/6/27.
//

#pragma once

#include <stdio.h>
#include "mk_list.h"
#include "mk_plock.h"

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

template <typename T>
class LockQueue : public MKList<T> {
public:
    LockQueue();
    void enqueue(T t);
    T dequeue(int milliseconds);
    bool start();
    void stop();
protected:
    MKPLocke mLocker;
};




MK_END
