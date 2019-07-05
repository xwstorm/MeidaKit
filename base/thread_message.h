//
//  thread_message.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#pragma once

#include <stdio.h>
#include "location.h"
MK_BEGIN
class MessageHandler;
class ThreadMessage {
public:
    enum ThreadMessageType {
        POST_MESSAGE,
        SEND_MESSAGE
    };
    ThreadMessage()
    : phandler(nullptr), message_id(0), ts_sensitive(0) {}
    
//    Location posted_from;
    MessageHandler* phandler;
    uint32_t message_id;
//    MessageData* pdata;
    int64_t ts_sensitive;
    ThreadMessageType messageType;
};
MK_END
