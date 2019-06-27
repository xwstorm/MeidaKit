//
//  mk_list.cpp
//  MediaKit
//
//  Created by xiewei on 2019/6/26.
//

#include "mk_list.h"

MK_BEGIN

template <typename T>
Node<T>::Node()
: value(nullptr)
, next(nullptr)
, prev(nullptr)
{
    
}

template <typename T>
Node<T>::Node(T t)
: value(t)
, next(nullptr)
, prev(nullptr)
{
}

/////////////////////////////

template <typename T>
MKList<T>::MKList()
: mHeader(nullptr)
, mTail(nullptr)
, mSize(0)
{
    
}
template <typename T>
void MKList<T>::addFront(T t) {
    Node<T> node = new Node<T>(t);
    if (mHeader == nullptr) {
        mHeader = node;
        mTail = node;
    } else {
        mHeader->prev = node;
        node->next = mHeader;
        mHeader = node;
    }
    mSize++;
}

template <typename T>
void MKList<T>::addBack(T t) {
    Node<T> node = new Node<T>(t);
    if (mTail == nullptr) {
        mHeader = node;
        mTail = node;
    } else {
        mTail->next = node;
        node->prev = mTail;
        mTail = node;
    }
}

template <typename T>
T MKList<T>::popFront() {
    if (mHeader == nullptr) {
        return nullptr;
    } else {
        Node<T>* node = mHeader;
        mSize--;
        if (mSize == 0) {
            mHeader = nullptr;
            mTail = nullptr;
        } else {
            mHeader = mHeader->next;
            mHeader->prev = nullptr;
        }
        T t = node->value;
        delete node;
        return t;
    }
}
template <typename T>
T MKList<T>::popBack() {
    if (mTail == nullptr) {
        return nullptr;
    } else {
        Node<T>* node = mTail;
        mSize--;
        if (mSize == 0) {
            mHeader = nullptr;
            mTail = nullptr;
        } else {
            mTail = mTail->prev;
            mTail->next = nullptr;
        }
        T t = node->value;
        delete node;
        return t;
    }
}
template <typename T>
bool MKList<T>::empty() {
    return mSize == 0;
}
MK_END
