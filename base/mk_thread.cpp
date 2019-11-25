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
        ThreadMessage* m = mPostQueue1.front();
        delete m;
        mPostQueue1.pop_front();
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
    
    for (auto it = mPostQueue1.begin(); it != mPostQueue1.end(); ++it) {
        if ((*it)->msg_delay > delay) {
            mPostQueue1.insert(it, msg);
            msg = nullptr;
            break;
        }
    }
    
    if (msg != nullptr) {
        mPostQueue1.push_back(msg);
    }
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
    mSendQueue1.push_back(&msg);
    lock.unlock();
    
    mMsgCV.notify_one();
    
    msg.wait();
}

bool MKThread::ProcessMessages() {
    while (!IsQuitting()) {
        std::unique_lock<std::mutex> lock(mMsgMutex);
        if (!mSendQueue1.empty()) {
            // return msg
            ThreadSendTaskMessage* msg = mSendQueue1.front();
            mSendQueue1.pop_front();
            lock.unlock();
            if (msg->phandler) {
                msg->phandler->OnMessage(msg->msg_data);
            }
            msg->signal();
            continue;
        } else if (!mPostQueue1.empty()) {
            // return msg
            ThreadMessage* msg = nullptr;
            
            while (msg == nullptr) {
                ThreadMessage* m = mPostQueue1.front();
                if (m->msg_delay <= 5) {
                    msg = m;
                    mPostQueue1.pop_front();
                    break;
                } else {
                    auto now = std::chrono::system_clock::now();
                    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m->triged_time).count();
                    int64_t timeToWait = m->msg_delay - elapsed;
                    if (timeToWait <= 5) {
                        msg = m;
                        mPostQueue1.pop_front();
                        break;
                    } else {
                        mMsgCV.wait_for(lock, std::chrono::milliseconds(timeToWait));
                    }
                }
            }
            if (!IsQuitting() && msg && msg->phandler) {
                lock.unlock();
                msg->phandler->OnMessage(msg->msg_data);
            }
            if (msg) {
                delete msg;
            }
            continue;
        } else {
            // empty
            mMsgCV.wait(lock);
        }
    } // while
    return false;
}

bool MKThread::IsQuitting() {
    return mIsQuiting;
}


MK_END
