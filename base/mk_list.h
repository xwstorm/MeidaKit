//
//  mk_list.h
//  MediaKit
//
//  Created by xiewei on 2019/6/26.
//



#include <stdio.h>
#include "av_base.h"
#include "event.h"
MK_BEGIN

template <typename T>
class Node {
public:
    Node();
    Node(T t);
    
    T value;
    Node* prev;
    Node* next;
};

template <typename T>
class MKList {
public:
    MKList();
    void addFront(T t);
    T popFront();
    
    void addBack(T t);
    T popBack();
    bool empty();
protected:
    Node<T>* mHeader;
    Node<T>* mTail;
    unsigned int mSize;
};


MK_END
