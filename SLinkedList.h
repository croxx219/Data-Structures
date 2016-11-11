#include "Node.h"
#include <iostream>
#include <cstddef>
#include <cassert>
using namespace std;

template<class T>
class SLinkedList{
private:
    Node<T> * head;
    int sz;

public:
    SLinkedList():head(NULL), sz(0){
    }
    bool empty() const{
        return head == NULL;
    }
    void push_back(const T & data){
        Node<T> *tmp_node = new Node<T>(data);
        Node<T> *ptr = head;
        if (ptr == NULL){
            head = tmp_node;
            sz++;
        }
        else{
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = tmp_node;
            sz++;
        }
    }

    int clear() {
        int count = 0;
        Node<T> *ptr = head;
        Node<T> * prev = head;
        while (ptr != NULL) {
            ptr = ptr->next;
            delete prev;
            prev = ptr;
            count++;
        }
        head = NULL;
        return count;
    }

    void printList() {
        Node<T> *ptr = head;
        while(ptr!=NULL) {
           cout << ptr->data << "-->";
            ptr = ptr->next;
        }
        if (this->empty())
            throw underflow_error("Empty\n");
       else
           cout << "end" << endl;
    }
};
