//
//  av_thread.cpp
//  MediaKitDemo
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#include "mk_thread.h"

MK_BEGIN

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
    std::unique_lock<std::mutex> lock(mMsgMutex);
    mIsQuiting = false;
    lock.unlock();
    mWThread = std::thread(MKThread::runProxy, this);
    return true;
}

void MKThread::close() {
    std::unique_lock<std::mutex> lock(mMsgMutex);
    mIsQuiting = true;
    while (!mPostQueue1.empty()) {
        ThreadMessage* m = mPostQueue1.back();
        delete m;
        mPostQueue1.pop();
    }
    lock.unlock();
    
    mMsgCV.notify_all();
    if (mWThread.joinable()) {
        mWThread.join();
    }
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

bool MKThread::Post(const MKLocation& posted_from,
                    MessageHandler* phandler,
                    int64_t delay,
                    int msg_tag,
                    MessageData* data) {
    ThreadMessage* msg = new ThreadPostTaskMessage();
    msg->phandler = phandler;
    msg->msg_data = data;
    msg->msg_delay = delay;
    if (delay >= 10) {
        msg->triged_time = std::chrono::system_clock::now();
    }
    std::unique_lock<std::mutex> lock(mMsgMutex);
    if (IsQuitting()) {
        return false;
    }
    mPostQueue1.push(msg);
    mMsgCV.notify_one();
    return true;
}

void MKThread::Send(const MKLocation& posted_from,
                    MessageHandler* phandler,
                    int msg_tag,
                    MessageData* data) {
    if (IsQuitting()) {
        return;
    }
    ThreadSendTaskMessage msg;
    msg.phandler = phandler;
    msg.msg_data = data;

    if (isCurrent()) {
        phandler->OnMessage(data);
        return;
    }
    std::unique_lock<std::mutex> lock(mMsgMutex);
    mSendQueue1.push(&msg);
    mMsgCV.wait(lock);
}

bool MKThread::ProcessMessages() {
    while (!IsQuitting()) {
        
        std::unique_lock<std::mutex> lock(mMsgMutex);
        if (!mSendQueue1.empty()) {
            // return msg
            ThreadSendTaskMessage* msg = mSendQueue1.back();
            mSendQueue1.pop();
            lock.unlock();
            if (msg->phandler) {
                msg->phandler->OnMessage(msg->msg_data);
            }
            msg->signal();
            continue;
        } else if (!mPostQueue1.empty()) {
            // return msg
            ThreadMessage* msg = nullptr;
            size_t size = mPostQueue1.size();
            int64_t minDelay = 0;
            auto start = std::chrono::system_clock::now();
            for (int i=0; i<size; ++i) {
                ThreadMessage* m = mPostQueue1.back();
                mPostQueue1.pop();
                if (m->msg_delay == 0) {
                    msg = m;
                    break;
                } else {
                    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(start - m->triged_time).count();
                    if (elapsed <= 2 ) {
                        msg = m;
                        break;
                    } else {
                        mPostQueue1.push(m);
                        minDelay = minDelay < elapsed ? minDelay : elapsed;
                    }
                }
            }
            if (minDelay > 0) {
                mMsgCV.wait_for(lock, std::chrono::milliseconds(minDelay));
            } else {
                if (msg && msg->phandler) {
                    lock.unlock();
                    msg->phandler->OnMessage(msg->msg_data);
                }
            }
            continue;
        } else {
            mMsgCV.wait(lock);
        }
    }
    return false;
}

bool MKThread::IsQuitting() {
    return mIsQuiting;
}


MK_END
