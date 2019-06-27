//
//  av_thread.hpp
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
    bool ProcessMessages(int cms);
    
    // template
    template <class ReturnT, class FunctorT>
    ReturnT Invoke(const Location& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<ReturnT, FunctorT> handler(std::forward<FunctorT>(functor));
        InvokeInternal(posted_from, &handler);
        return handler.MoveResult();
    }

protected:
    bool IsQuitting();
    
    void InvokeInternal(const Location& posted_from,
                        MessageHandler* handler);
    // post
    void Post(const Location& posted_from,
              MessageHandler* phandler);
    
    // send
    void Send(const Location& posted_from,
              MessageHandler* phandler);
    
    ThreadMessage* GetMsg();
    void Dispatch(ThreadMessage* msg);
    
    
protected:
    PriorityQueue<ThreadMessage*> mQueue;
};
MK_END
