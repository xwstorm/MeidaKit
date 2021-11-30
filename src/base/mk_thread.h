//
//  mk_thread.h
//  MediaKit
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#pragma once
#include <thread>
#include <list>
#include "base/mk_base.h"
#include "base/location.h"
#include "thread_message.h"
#include "message_handler.h"

MK_BEGIN
class MKThread {
public:
    MKThread(const char* name = nullptr);
    bool open();
    void close();
    
    // template
    template <class ReturnT, class FunctorT>
    ReturnT Invoke(const MKLocation& posted_from, FunctorT&& functor) {
        FunctorMessageHandler<ReturnT, FunctorT> handler(std::forward<FunctorT>(functor));
        Send(posted_from, &handler);
        return handler.MoveResult();
    }
    
    template <class ReturnT, class FunctorT>
    bool AsyncInvoke(const MKLocation& posted_from, FunctorT&& functor, uint32_t tag = 0) {
        FunctorMessageHandler<void, FunctorT>* handler = new FunctorMessageHandler<void, FunctorT>(std::forward<FunctorT>(functor));
        return Post(posted_from, handler, 0);
    }
    
    template <class ReturnT, class FunctorT>
    bool AsyncInvokeDelay(const MKLocation& posted_from, FunctorT&& functor, int64_t millsecond, uint32_t tag = 0) {
        FunctorMessageHandler<void, FunctorT>* handler = new FunctorMessageHandler<void, FunctorT>(std::forward<FunctorT>(functor));
        return Post(posted_from, handler, millsecond);
    }
    

protected:
    bool isCurrent();
    bool ProcessMessages();
    
    bool IsQuitting();
    // post
    bool Post(const MKLocation& posted_from,
              MessageHandler* phandler,
              int64_t delay,
              int msg_tag = 0,
              MessageData* data = nullptr);
    
    // send
    void Send(const MKLocation& posted_from,
              MessageHandler* phandler,
              int msg_tag = 0,
              MessageData* data = nullptr);
    
    void setName();
private:
    static void runProxy(MKThread* thread);
    virtual void run();
protected:
    char*       mName;
    bool        mIsQuiting;
    
    std::thread mWThread;
    
    // message queue
    std::list<ThreadSendTaskMessage*> mSendQueue1;
    std::list<ThreadMessage*> mPostQueue1;
    
    std::mutex mMsgMutex;
    std::condition_variable mMsgCV;
};
MK_END
