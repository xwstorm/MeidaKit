//
//  av_thread.cpp
//  MediaKitDemo
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#include "av_thread.h"
#include "message_handler.h"

MK_BEGIN
MKThread::MKThread() {
    
}

MKThread::MKThread(const char* name)
: mName(nullptr)
{
    if (name != nullptr) {
        size_t len = strlen(name);
        if (len > 20) {
            len = 20;
        }
        mName = (char*)malloc((len+1) * sizeof(char));
        memcpy(mName, name, len);
        mName[len] = 0x0;
    }
}


bool MKThread::open() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    int error_code = pthread_create(&mThread, &attr, PreRun, this);
    if (mName != nullptr) {
//        pthread_setname_np(mThread, mName);
        pthread_setname_np(mName);
    }
    return true;
}

void MKThread::close() {
    
    pthread_join(mThread, 0);
}

bool MKThread::start() {
    
//    mQueue.start();
    return true;
}

void MKThread::stop() {
//    mQueue.stop();
}

void MKThread::Run() {
    
    
}

void* MKThread::PreRun(void* pv) {
    MKThread* thread = static_cast<MKThread*>(pv);
    thread->Run();
    
    return nullptr;
}

template <class ReturnT, class FunctorT>
ReturnT Invoke(const Location& posted_from, FunctorT&& functor) {
    FunctorMessageHandler<ReturnT, FunctorT> handler(std::forward<FunctorT>(functor));
    Send(posted_from, &handler);
    return handler.MoveResult();
}

bool MKThread::isCurrent() {
    return false;
}

bool MKThread::ProcessMessages(int cmsLoop) {
    while (!IsQuitting()) {
        // get msg
        ThreadMessageStruct msg = msg = GetMsg();
        if(msg != nullptr) {
            Dispatch(msg);
        }
    }
    return false;
}
 
void MKThread::Post(const Location& posted_from,
                    MessageHandler* phandler) {
    ThreadMessage* msg = new ThreadMessage();
    msg->phandler = phandler;
    mQueue.enqueue(msg);
}

void MKThread::Send(const Location& posted_from,
                    MessageHandler* phandler) {
    if (IsQuitting()) {
        return;
    }
    // send message to queue
    ThreadMessage* msg = new ThreadMessage();
    msg->phandler = phandler;
    
    if (isCurrent()) {
        phandler->OnMessage(msg);
        return;
    }
    mQueue.enqueue(msg, ThreadQueue::HIGHT_PRIORITY);
    // waiting
    
    
}

bool MKThread::IsQuitting() {
    return false;
}

ThreadMessage* MKThread::GetMsg() {
    ThreadMessage* msg = mQueue.dequeue();
    return msg;
}

void MKThread::Dispatch(ThreadMessage* msg) {
    msg->phandler->OnMessage(msg);
}

MK_END
