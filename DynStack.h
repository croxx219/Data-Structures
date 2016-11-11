#pragma once
#include<iostream>
#include<stdexcept>
#include<string>

using namespace std;

template <class myType>
class DynStack {
private:
    myType *array;
    int count;
    int initialSize;
    int arraySize;
public:
    DynStack(int n = 13) {
        if ((n == 0) || (n < 0)) {
            initialSize = arraySize = 1;
        }
        else
            initialSize = arraySize = n;
        array = new myType[initialSize];
        count = -1;  // Initialize to -1 so that if array is empty, element is stored at 0
    }
    
    bool empty() const {
        return count == -1;
    }

    myType top() const {
        if (this->empty())
            throw underflow_error("Stack is empty\n");
        return array[count];
    }

    int size() const {
        if (this->empty())
            throw underflow_error("Stack is empty\n");
        return count+1;
    }
    
    int capacity() const {
        return arraySize;
    }
    
    
    void push(myType const & data) {
        if (count < arraySize - 1) {
            array[++count] = data;
        }

        else { //Array is full
            arraySize *= 2;
            myType *tmpArray = new myType[arraySize];
            for (int i = 0; i <= count;i++)
                tmpArray[i] = array[i];
            delete[] array;
            array = tmpArray;
            array[++count] = data;
        }
    }
    
    
    myType pop() {
        if (this->empty())
            throw underflow_error("Stack is empty\n");

       myType tmp = array[count];
       array[count--].clear();
        
        if (((count+1) <= 0.25*arraySize) && (arraySize > initialSize)) {
            arraySize /= 2;
            myType *tmpArray = new myType[arraySize];
            for (int i = 0; i <= count;i++)
                tmpArray[i] = array[i];
            delete[] array;
            array = tmpArray;

            cout << "Size was halved" << endl;
        }

        return tmp;
    }
   
    void clear() {
        delete[] array;
        array = new myType[initialSize];
        arraySize = initialSize;
        count = -1;
    }
    
    int erase(myType const &data) {
        if (this->empty())
            throw underflow_error("Stack is empty\n");
        int sum = 0;
        DynStack *Dtmp = new DynStack<myType>(arraySize);
        
        while(!this->empty()) {
           
            myType tmp = this->pop();
            if (tmp == data) {
                tmp.clear();      // Clear method for string
                sum++;
            }
            else
                Dtmp->push(tmp);
        }
        
        while (!Dtmp->empty()) {
            this->push(Dtmp->pop());
        }
        
        return sum;
    }

    void display() {
        if (this->empty()) {
            cout << "Bottom->";
            return;
        }
        
        string x = this->pop();
        display();
        this->push(x);
        cout << x << " ";
    }
    
    ~DynStack() {
        delete[] array;
        count = -1;
        initialSize = arraySize = 0;
        cout << "Destructor called" << endl;
    }


};
