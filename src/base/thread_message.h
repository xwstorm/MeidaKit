//
//  thread_message.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#pragma once

#include "base/mk_base.h"
#include "location.h"
#include "message_handler.h"
#include "mk_lock.h"
MK_BEGIN
class MessageHandler;
class MessageData;

struct ThreadMessage {
    enum ThreadMessageType {
        POST_MESSAGE,
        SEND_MESSAGE
    };
    ThreadMessage()
    : phandler(nullptr)
    , message_id(0)
    , ts_sensitive(0)
    , msg_delay(0) {}
    
    virtual ~ThreadMessage(){};
    MKLocation posted_from;
    MessageHandler* phandler;
    uint32_t message_id;
    MessageData* msg_data;
    int64_t ts_sensitive;
    int64_t msg_delay;
    std::chrono::system_clock::time_point triged_time;
};

struct ThreadPostTaskMessage : public ThreadMessage {
public:
    ~ThreadPostTaskMessage() {
        if (phandler) {
            delete phandler;
        }
    }
};

struct ThreadSendTaskMessage : public ThreadMessage {
public:
    void wait() {
        mLock.wait();
    };
    void signal() {
        mLock.notifyAll();
    };
private:
    MKLock mLock;
};
MK_END
