//
//  message_handler.h
//  MediaKit
//
//  Created by xiewei on 2019/6/17.
//

#pragma once
#include <stdio.h>
#include <utility>
#include "base/mk_base.h"
MK_BEGIN
class ThreadMessage;


class MessageData {
public:
    MessageData() {}
    virtual ~MessageData() {}
};

class MessageHandler {
public:
    virtual ~MessageHandler(){};
    virtual void OnMessage(MessageData* msg) = 0;
    
protected:
    MessageHandler() {}
};

template <class ReturnT, class FunctorT>
class FunctorMessageHandler : public MessageHandler {
public:
    explicit FunctorMessageHandler(FunctorT&& functor)
    : mFunctor(std::forward<FunctorT>(functor)) {}
    void OnMessage(MessageData* msg) override {
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
    void OnMessage(MessageData* msg) override{
        mFunctor();
    }
    void result() const {}
    void MoveResult() {}
    
private:
    FunctorT mFunctor;
};
MK_END
