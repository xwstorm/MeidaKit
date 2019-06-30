//
//  av_thread.cpp
//  MediaKitDemo
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#include "av_thread.hpp"
MK_BEGIN
MKThread::MKThread() {
    
}

void MKThread::InvokeInternal(const Location& posted_from,
                            MessageHandler* handler) {
    Send(posted_from, handler);
    
}

bool MKThread::ProcessMessages(int cmsLoop) {
    while (!IsQuitting()) {
        // get msg
        ThreadMessage* msg;
        msg = GetMsg();
        if(msg != nullptr) {
            Dispatch(msg);
        }
    }
    return false;
}
 
void MKThread::Post(const Location& posted_from,
                    MessageHandler* phandler) {
}

void MKThread::Send(const Location& posted_from,
                    MessageHandler* phandler) {
    
}

bool MKThread::IsQuitting() {
    return false;
}

ThreadMessage* MKThread::GetMsg() {
    
    while (true) {
        // process send message
        
        // block at post message
        return nullptr;
    }
    return nullptr;
}

void MKThread::Dispatch(ThreadMessage* msg) {
    msg->phandler->OnMessage(msg);
}

MK_END
