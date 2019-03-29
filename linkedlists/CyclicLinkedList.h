#pragma once
#include <iostream>
#include <stdexcept>
#include "SingleNode.h"

using namespace std;

template <class myType>
class CyclicLinkedList
{
private:
    SingleNode<myType> *head;
    SingleNode<myType> *tail;
    int sizeList;

public:
    CyclicLinkedList():sizeList(0), head(nullptr), tail(nullptr) {
    };

    int size() const {
        return sizeList;
    };

    bool empty() const { return sizeList == 0; };

    myType front() const {
        if (this->empty())
            throw underflow_error("Empty\n");
        return head->getData();
    }

    myType back() const {
        if (this->empty())
            throw underflow_error("Empty\n");
        return tail->getData();
    };

    SingleNode<myType> *Head() const { 
        return head; 
    };
    
    SingleNode <myType> *Tail() const { 
        return tail;
    };

    int count(myType const & data) const {
        int sum = 0;
        SingleNode<myType> *tempNode = head;
        
        for (int i = 0; i < sizeList; i++) {
            if (tempNode->getData() == data)
                sum++;
            tempNode = tempNode->next;
        }
        return sum;
    };

    void push_front(myType const & data) {
        SingleNode<myType> *newNode = new SingleNode<myType>(data, head);
        head = newNode;
        if (this->empty()) {
            tail = newNode;
        }
        tail->next = head;
        sizeList++;
            
    };

    void push_back(myType const & data) {
        SingleNode<myType> *newNode = new SingleNode<myType>(data, head);
        if (this->empty()) {
            head = newNode;
            tail = head;
        }
        tail->next = newNode;   // Tail is now the newNode
        tail = newNode;
        
        sizeList++;
    };

    myType pop_front() {
        if (this->empty())
            throw underflow_error("Empty\n");

        SingleNode<myType> *front = head;
        head = head->next;
        tail->next = head;

        myType data = front->getData();
        delete front;
        --sizeList;
        return data;
    };

    // Menu program is going to make this method run only when 
    // there is at least one element in the least.

    int erase(myType const & data) {
        int delNodes = 0; //Nodes deleted
        
        SingleNode<myType> *prev = head;
        SingleNode<myType> *curr = head;
      
        while (curr->next != head) {
            if (curr->getData() == data) {
                if (curr == head){ // first element 
                    head = head->next;
                    curr = head;
                    delete prev; 
                }
            
                else { // middle element
                    SingleNode<myType> *tmp = curr->next;
                    curr->data = curr->next->getData();
                    curr->next = curr->next->getNext();
                    delete tmp;
                }
                // curr goes out of scope for either case and gets destroyed by the destructor
                delNodes++;
            }
            
            tail->next = head;
            prev = curr;
            curr = curr->next;
            
        }

        if (curr->data == data) {
            prev->next = head;
            delete curr;
            delNodes++;
            tail = prev;
        }

        if (prev->data == data) {
            head = prev->next;
            prev = curr;
            tail->next = head;
            delNodes++;
        }
        if (delNodes == 0) {
            cout << "Element not in list\n";
            return 0;
        }
        else {
            sizeList -= delNodes;
            return delNodes;
        }
    }

    void printList() {
        SingleNode<myType> *ptr = head;
        for (int i = 0; i<sizeList; i++) {
            cout << "Node[" << i << "]=" << ptr->getData() << "-->";
            ptr = ptr->next;
        }
        if (this->empty())
            throw underflow_error("Empty\n");
        else
            cout << "head" << endl;
    }

    ~CyclicLinkedList() {
        if (this->empty()) {
            cout << "List is empty\n";                //If list is empty there is nothing to be destroyed
            return;
        }
        SingleNode<myType> *curr = head;
        SingleNode<myType> *prev = head;
        while(curr->next!=head)
        {
            curr = curr->next;
            delete prev;
            prev = curr;    
        }
        head = nullptr;
        sizeList = 0;
        cout << "Destructor called\n";
    };
};


