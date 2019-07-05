//
//  message_handler.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#pragma once
#include <stdio.h>
#include <utility>
#include "av_base.h"
MK_BEGIN
class ThreadMessage;
class MessageHandler {
public:
    virtual ~MessageHandler();
    virtual void OnMessage(ThreadMessage* msg) = 0;
    
protected:
    MessageHandler() {}
};


template <class ReturnT, class FunctorT>
class FunctorMessageHandler : public MessageHandler {
public:
    explicit FunctorMessageHandler(FunctorT&& functor)
    : mFunctor(std::forward<FunctorT>(functor)) {}
    virtual void OnMessage(ThreadMessage* msg) {
        mResult = mFunctor();
    }
    ReturnT MoveResult() {
        return std::move(mResult);
    }
    
private:
    FunctorT mFunctor;
    ReturnT mResult;
};

// Specialization for ReturnT of void.
template <class FunctorT>
class FunctorMessageHandler<void, FunctorT> : public MessageHandler {
public:
    explicit FunctorMessageHandler(FunctorT&& functor)
    : mFunctor(std::forward<FunctorT>(functor)) {}
    virtual void OnMessage(ThreadMessage* msg) { mFunctor(); }
    void result() const {}
    void MoveResult() {}
    
private:
    FunctorT mFunctor;
};
MK_END
