//
//  thread_message.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#pragma once

#include "av_base.h"
#include "location.h"
#include "message_handler.h"
#include "mk_lock.h"
MK_BEGIN
class MessageHandler;
class MessageData;

struct ThreadMessage : public MessageData {
    enum ThreadMessageType {
        POST_MESSAGE,
        SEND_MESSAGE
    };
    ThreadMessage()
    : phandler(nullptr), message_id(0), ts_sensitive(0) {}
    
    MKLocation posted_from;
    MessageHandler* phandler;
    uint32_t message_id;
    MessageData* msg_data;
    int64_t ts_sensitive;
    ThreadMessageType messageType;
    
    virtual void wait() {};
    virtual void signal() {};
};

struct ThreadSendMessage : public ThreadMessage {
public:
    void wait() override {
        mLock.wait();
    };
    void signal() override {
        mLock.notifyAll();
    };
private:
    MKLock mLock;
};
MK_END
