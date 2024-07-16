#pragma once
#include<bits/stdc++.h>
using namespace std;

template <typename E> class List {
public:
    List(){}
    virtual ~List(){}
    virtual void clear()=0;
    virtual void insert(E* item) = 0;
    virtual void append(E* item) = 0;
    virtual void remove(const string& item) = 0;
    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length() = 0;
    virtual int currPos() = 0;
    virtual void moveToPos(int pos) = 0;
    virtual string getValue() = 0;
    virtual E* search(const string& item) = 0;
};

