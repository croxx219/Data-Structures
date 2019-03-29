#pragma once
#include <iostream>
#include <stdexcept>
#include "SLinkedList.h"

using namespace std;

template <class myType>
class TreeNode {
private:
    int key;
    myType data;
    TreeNode<myType> *parent;
    SLinkedList < TreeNode<myType> * > *children;
    template<class U> friend class LinkedTree;
public:
    TreeNode()
    {
        key = 0;
        parent = NULL;
        children = new SLinkedList< TreeNode< myType > * >();
    }

    TreeNode(const myType & data):TreeNode()
    {
        this->data = data;
    }
    int getKey() { return key; }
    myType getData() { return data; }
    TreeNode<myType> * getParent() { return parent; }
};