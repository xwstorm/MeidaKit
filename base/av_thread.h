//
//  av_thread.h
//  MediaKit
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <list>
#include "av_base.h"
#include "location.h"
#include "thread_message.h"
#include "message_handler.h"
#include "event.h"
#include "queue.h"
#include "priority_queue.h"
#include <thread>
#include "mk_lock.h"

MK_BEGIN
class MKThread {
public:
    MKThread();
    MKThread(const char* name);
    bool open();
    void close();
    bool start();
    void stop();
    
    bool ProcessMessages();
    
    // template
    template <class ReturnT, class FunctorT>
    ReturnT Invoke(const MKLocation& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<ReturnT, FunctorT> handler(std::forward<FunctorT>(functor));
        Send(posted_from, handler);
        return handler.MoveResult();
    }
    
    template <class ReturnT, class FunctorT>
    ReturnT AsyncInvoke(const MKLocation& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<void, FunctorT> handler(std::forward<FunctorT>(functor));
        Post(posted_from, handler);
    }
    
    bool isCurrent();

protected:
    typedef ThreadMessage* ThreadMessageStruct;
    
    bool IsQuitting();
    // post
    void Post(const MKLocation& posted_from,
              MessageHandler* phandler,
              int msg_tag = 0,
              MessageData* data = nullptr);
    
    // send
    void Send(const MKLocation& posted_from,
              MessageHandler* phandler,
              int msg_tag = 0,
              MessageData* data = nullptr);
    
    ThreadMessageStruct GetMsg();
    void Dispatch(ThreadMessage* msg);
    void setName();
private:
    static void runProxy(MKThread* thread);
    virtual void run();
protected:
    typedef PriorityQueue<ThreadMessage*> ThreadQueue;
    ThreadQueue mQueue;
    
    pthread_t   mThread;
    char*       mName;
    
    std::thread mWThread;
    MKLock      mLock;
};
MK_END
