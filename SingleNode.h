#pragma once
#include <iostream>

using namespace std;
static int num = 0;

template <class myType>
class SingleNode {
private:
    myType data;
    SingleNode * next;
    template <class U>
    friend class CyclicLinkedList;
public:
    
    SingleNode(const myType & data, SingleNode * next) {
        this->data = data;
        this->next = next;
    }

    ~SingleNode() {};

    myType getData() const {
        return data;
    };

    SingleNode *getNext() const
    {
        return next;
    };
};

