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
    mWThread = std::thread(MKThread::runProxy, this);
    return true;
}
#ifdef MK_WIN32
void MKThread::setName() {
    if (mName != nullptr) {
    }
}
#else
#include <pthread.h>
void MKThread::setName() {
    if (mName != nullptr) {
        pthread_setname_np(mName);
    }
}
#endif

void MKThread::close() {
    if (mWThread.joinable()) {
        mWThread.join();
    }
}

bool MKThread::start() {
    
//    mQueue.start();
    return true;
}

void MKThread::stop() {
//    mQueue.stop();
}

void MKThread::runProxy(MKThread* thread) {
    thread->run();
}

void MKThread::run() {
    // prerun
    setName();
    ProcessMessages();
    // after run
}


bool MKThread::isCurrent() {
    return false;
}

void MKThread::Post(const MKLocation& posted_from,
                    MessageHandler* phandler,
                    int msg_tag,
                    MessageData* data) {
    ThreadMessage* msg = new ThreadMessage();
    msg->phandler = phandler;
    msg->msg_data = data;
    mQueue.enqueue(msg);
}

void MKThread::Send(const MKLocation& posted_from,
                    MessageHandler* phandler,
                    int msg_tag,
                    MessageData* data) {
    if (IsQuitting()) {
        return;
    }
    // send message to queue
    ThreadMessage* msg = new ThreadMessage();
    msg->phandler = phandler;
    msg->msg_data = data;
    
    
    if (isCurrent()) {
        phandler->OnMessage(msg);
        return;
    }
    mQueue.enqueue(msg, ThreadQueue::HIGHT_PRIORITY);
    // waiting
    // phandler.wait
    
}

bool MKThread::ProcessMessages() {
    while (!IsQuitting()) {
        // get msg
        ThreadMessageStruct msg = GetMsg();
        if(msg != nullptr) {
            Dispatch(msg);
        }
    }
    return false;
}

void MKThread::Dispatch(ThreadMessage* msg) {
    if(msg->phandler) {
        msg->phandler->OnMessage(msg);
    }
}

bool MKThread::IsQuitting() {
    return false;
}

ThreadMessage* MKThread::GetMsg() {
    ThreadMessage* msg = mQueue.dequeue();
    return msg;
}

MK_END
