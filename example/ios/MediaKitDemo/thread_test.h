//
//  thread_test.cpp
//  MediaKitDemo
//
//  Created by xiewei on 2019/10/31.
//  Copyright © 2019 xiewei. All rights reserved.
//
#pragma once
#include <stdio.h>
#include "base/mk_thread.h"
using namespace mk;
class ThreadTest {
public:
    ThreadTest()
    : mThread1("thread1")
    , mThread2("thread2") {
        mThread1.open();
        
        
        mThread2.open();
    }
    void func1() {
        // in thread1
        printf("thread 1\n");
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mThread2.AsyncInvoke<void>(CALL_FROM_HERE, [this]() {
            func2();
        });
    }
    
    void func2() {
        // in thread2
        printf("thread 2\n");
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mThread1.AsyncInvoke<void>(CALL_FROM_HERE, [this]() {
            func1();
        });
    }
    
protected:
    
    MKThread mThread1;
    MKThread mThread2;
};
