#pragma once

#include <stdexcept>
#include <exception>
#include <iostream>
using namespace std;

template <typename Type>
class DynQueue
{
private:
    //Data Members
    Type *array; //a pointer to an instance of type
    int ihead; //a head index
    int itail; //a tail index
    int count; //a counter
    int initialSize; //the initial size of the array
    int arraySize; //the current size of the array
public:
    //constructor
    DynQueue(int n = 13);
    //destructor
    ~DynQueue();

    //Accessors
    Type front() const;

    Type back() const;

    int size() const;

    bool empty() const;

    int capacity() const;

    void display();

    //mutators
    void enqueue(Type const &data);

    Type dequeue();

    void clear();

    int erase(Type const &data);
};

template <typename Type>
DynQueue<Type>::DynQueue(int n)
{
    //If the argument is either 0 or a negative integer,
    if (n == 0 || n < 0)
    {
        //set the initial capacity of the array to 1
        array = new Type[1];
    }
    else
    {
        //else set the initial capacity of the array to default
        array = new Type[n];
    }
    initialSize = arraySize = n;
    itail = 0;
    ihead = 0;
    count = 0;

}


template <typename Type>
DynQueue<Type>::~DynQueue()
{
    delete[] array;
    count = initialSize = arraySize = ihead = itail = 0;
}

//Returns the object at the front of the queue. It may throw a underflow exception. (O(1))
template <typename Type>
Type DynQueue<Type>::front() const
{
    if (empty())
    {
        throw underflow_error(" front is empty, nothing to retrieve");
    }
    return array[ihead];
}

//Returns the object at the back of the queue. It may throw a underflow exception. (O(1))
template <typename Type>
Type DynQueue<Type>::back() const
{
    if (empty())
    {
        throw underflow_error("back is empty, nothing to retrieve");
    }
    return array[itail];
}

//Returns the number of elements currently stored in the queue. (O(1))
template <typename Type>
int DynQueue<Type>::size() const
{
    return count;
}

//Returns true if the queue is empty, false otherwise
template <typename Type>
bool DynQueue<Type>::empty() const
{
    if (size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Returns the current size of the array.
template <typename Type>
int DynQueue<Type>::capacity() const
{
    return arraySize;
}

//Insert the new element at the back of the queue.If the array is full, the size of the array is rst doubled.
template <typename Type>
void DynQueue<Type>::enqueue(Type const &data)
{
    //if array is full
    if (count == arraySize)
    {
        //initialize a new array of doubled size
        Type *tempArray = new Type[arraySize * 2];

        //wrap around
        if (itail < ihead)
        {
            int x = 0;
            for (int i = ihead; i < arraySize; ++i) {
                tempArray[x] = array[i];
                ++x;
            }
            //front to tail
            for (int i = 0; i <= itail; ++i) {
                tempArray[x] = array[i];
                ++x;
            }
            //deallocate, set array pointer to new array
            delete[] array;
            array = tempArray;
            //reset back to initial state.
            ihead = 0;
            itail = arraySize - 1;
            array[x] = data;
            //enqueue
            ++itail;
            array[itail] = data;
        }
        //no wrap around
        else
        {
            for (int i = 0; i < arraySize; ++i)
            {
                tempArray[i] = array[i];
            }
            //deallocate, set array pointer to new array
            delete[] array;
            array = tempArray;
            //reset back to initial state.
            ihead = 0;
            itail = arraySize - 1;
            //enqueue
            ++itail;
            array[itail] = data;
        }
        //update array size
        arraySize = arraySize * 2;
    }
    else
    {
        if (itail == (arraySize - 1))
        {
            itail = 0;
            array[itail] = data;
        }
        else if (count == 0)
        {
            array[itail] = data;
        }
        else
        {
            ++itail;
            array[itail] = data;
        }
    }
    ++count;
}

//Removes the element at the front of thequeue.If, 
//after the element is removed, the array is 1 / 4 full and 
//the array size is greater than the initial size, 
//the size of the array is halved.This may throw a underflow exception.
template <typename Type>
Type DynQueue<Type>::dequeue()
{
    if (empty())
    {
        throw underflow_error("empty, nothing left to dequeue.");
    }

    //retrieve element 
    Type temp;
    temp = array[ihead];

    if (ihead == arraySize - 1)
    {
        if (ihead > itail)
        {
            ihead = 0;
        }
        else
        {
            ihead = 0;
            itail = 0;
        }

    }
    else if (count == 1)
    {
        ihead = 0;
        itail = 0;
    }

    else
    {
        ++ihead;
    }
    --count;

    //after the element is removed, the array is 1/4 full
    if (count == (arraySize / 4))
    {
        if (initialSize <= (arraySize / 2))
        {
            //inintialize a new array of size halved
            Type * tempArray = new Type[arraySize / 2];

            if (ihead > itail)
            {
                int x = 0;
                for (int i = ihead; i < arraySize; ++i)
                {
                    tempArray[x] = array[i];
                    ++x;
                }

                for (int i = 0; i <= itail; ++i) {
                    tempArray[x] = array[i];
                    ++x;
                }
            }

            else
            {
                for (int i = 0; i < arraySize; ++i)
                {
                    tempArray[i] = array[i];
                }
            }
            //deallocate the array
            delete[] array;

            //reset back to initial state
            ihead = 0;
            itail = arraySize - 1;
            array = tempArray;
            arraySize = arraySize / 2;
        }
    }
    return temp;
}

//Removes all the elements in the queue. The array is resized to the initial size.
template <typename Type>
void DynQueue<Type>::clear()
{
    // removes all element, reset array back to initial state
    delete[] array;
    array = new Type[initialSize];
    arraySize = initialSize;
    ihead = 0;
    itail = initialSize - 1;
    count = 0;
}

//Remove the elements(from the front) in the structure that contains the element equal to the argument
//(use== to to test for equality with the retrieved element).
template<typename Type>
int DynQueue<Type>::erase(Type const & data)
{
    if (this->empty())
    {
        throw underflow_error("Queue is empty");

    }
    int sum = 0;
    DynQueue *tempArray = new DynQueue<Type>(arraySize);

    while (!this->empty())
    {
        Type temp = this->dequeue();
        if (temp == data)
        {
            temp.clear();
            sum++;
        }
        else
        {
            tempArray->enqueue(temp);
        }
    }
    while (!tempArray->empty())
    {
        this->enqueue(tempArray->dequeue());
    }
    return sum;
}

//Prints the content of the Queue.
template<class Type>
void DynQueue<Type>::display()
{

    int count = size();

    while (count > 0)
    {
        string x = this->dequeue();
        cout << x << " ";
        this->enqueue(x);
        count--;
    }
}
