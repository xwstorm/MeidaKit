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
#include "thread_message.h"
#include "message_handler.h"
#include "event.h"
#include "queue.h"
MK_BEGIN
class MKThread {
public:
    MKThread();
    MKThread(const char* name);
    bool open();
    void close();
    bool start();
    void stop();
    
    bool ProcessMessages(int cms);
    
    // template
    template <class ReturnT, class FunctorT>
    ReturnT Invoke(const Location& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<ReturnT, FunctorT> handler(std::forward<FunctorT>(functor));
        Send(posted_from, handler);
        return handler.MoveResult();
    }
    
    template <class ReturnT, class FunctorT>
    ReturnT AsyncInvoke(const Location& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<void, FunctorT> handler(std::forward<FunctorT>(functor));
        Post(posted_from, handler);
    }
    
    bool isCurrent();

protected:
    virtual void Run();
    
    
    typedef ThreadMessage* ThreadMessageStruct;
    
    static void* PreRun(void* pv);
    
    bool IsQuitting();
    // post
    void Post(const Location& posted_from,
              MessageHandler* phandler);
    
    // send
    void Send(const Location& posted_from,
              MessageHandler* phandler);
    
    ThreadMessageStruct GetMsg();
    void Dispatch(ThreadMessage* msg);
    
    
protected:
    typedef PriorityQueue<ThreadMessage*> ThreadQueue;
    ThreadQueue mQueue;
    
    pthread_t   mThread;
    char*       mName;
};
MK_END
