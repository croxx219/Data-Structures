
#include"DoubleNode.h"
#include <stdexcept>
#include <exception>
#include<iostream>
#include<cassert>
#include<cstdio>
#include<cstdlib>
using namespace std;


template<class Type>
class DoublyLinkedList {
private:
	//Data Members
	DoubleNode<Type> *head_of_list; //A pointer to the head of the list, referred to as the head pointer.
	DoubleNode<Type> *tail_of_list; //A pointer to the tail of the list, referred to as the tail pointer.
	int size_of_linkedlist; //An integer that holds the size of the linked list. The number of elements in the list.

public:
	//Constructor
	DoublyLinkedList();
	//Destructor
	~DoublyLinkedList();

	//Accessors
	int size() const; //returns the number of items in the list

	bool empty() const; //returns true if list is empty, false otherwise

	Type front() const; // retrieves the object stored in the node pointed to by the head pointer. This function throws a underflow if the list is empty
	
	Type back() const; //Retrieves the object stored in the node pointed to by the tail pointer. This function throws a underflow if the list is empty
	
	DoubleNode<Type> *head()const;//returns the head pointer
	
	DoubleNode<Type> *tail()const; //returns the tail pointer
	
	int count(const Type&) const; //returns the number of nodes in the linked list storing a value equal to the argument.

	//Mutator
	void push_front(const Type&); //creates a new DoubleNode<Type> storing the argement, the next pointer of which is set to the current head pointer.
								  //the head pointer is set to this new now. If the list was originally empty, the tail pointer is set to point to the new node.

	void push_back(const Type&); //similar to push_front, this place a new node at the back of the list.

	
	Type pop_front(); //Delete the node at the front of the linked list and, as necessary, update the head and tail pointers.
					  //Return the object stored in the node being popped. Throw an undeflow exception if the list is empty*/


	int erase(const Type&); //Delete the node(s) (from the fornt) in the linked list that contains the element equal to the argement(use == to to test
							//for equality with the retrieved delement). As necessary, update the head and tail pointers and the next pointer of any other 
							//node within the list. return the number of nodes that were deleted.*/

	void printlst() const;
	//Friends
	//This class has no friends/

};

//creates an empty list
//sets all member variables to 0 or nullptr, as appropriate.
template<class Type>
DoublyLinkedList<Type>::DoublyLinkedList():
	head_of_list(nullptr), tail_of_list(nullptr), size_of_linkedlist(0)
{	
}


//delete each of the nodes in the linked list.
template <class Type>
DoublyLinkedList<Type>::~DoublyLinkedList()
{
	//while the list is not empty, calling pop_front() to delete each of the nodes.
	while (!empty())
	{
		pop_front();

	}
}

//returns the number of items in the list.
template<class Type>
int DoublyLinkedList<Type>::size() const 
{
	return size_of_linkedlist;
}

//Returns true if the list is empty, false otherwise.
template<class Type>
bool DoublyLinkedList<Type>::empty() const 
{
	if (head_of_list == 0)
	{
		return true;
	}
	return false;
}

//Retrieves the object stored in the node pointed to by the head pointer.
//This function throws a undefrow if the list is empty.
template<class Type>
Type DoublyLinkedList<Type>::front() const 
{
	if (empty())
	{
		throw underflow_error("List is empty, there is nothing to retrieve.");
	}

	return head_of_list->getData();
}

//Retrieves the object stored in the node pointed to by the tail pointer.
//This function throws a undefrow if the list is empty.
template<class Type>
Type DoublyLinkedList<Type>::back() const 
{
	if (empty())
	{
		throw underflow_error("List is empty, there is nothing to retrieve");
	}
	return tail_of_list->getData();
}

//Returns the head pointer.
template<class Type>
DoubleNode<Type> *DoublyLinkedList<Type>::head() const 
{
    if (empty())
    {
        throw underflow_error("List is empty, there is nothing to retrieve.");
    }
	return head_of_list;
}

//Returns the tail pointer.
template<class Type>
DoubleNode<Type> *DoublyLinkedList<Type>::tail() const 
{
    if (empty())
    {
        throw underflow_error("List is empty, there is nothing to retrieve.");
    }
	return tail_of_list;
}

//Returns the number of nodes in the linked list storing a value equal to the argument.
template<class Type>
int DoublyLinkedList<Type>::count(const Type &data) const 
{
	int count = 0;
	DoubleNode<Type> * ptr = head();

	while (ptr != nullptr)
	{
		if (ptr->getData() == data)
		{
			++count;
		}
		ptr = ptr->getNext();
	}
	return count;
	cout << " Number of elements are: " << count << endl;

}

//insert element at the begining
template <class Type>
void DoublyLinkedList<Type>::push_front(const Type &data) 
{
	DoubleNode<Type> *newNode;
	if (empty())
	{
		newNode = new DoubleNode<Type>(data, nullptr, nullptr);// Creates a new DoubleNode< Type > storing the argument,
		head_of_list= tail_of_list = newNode; // If the list was originally empty, the tail pointer is set to point to the new node.

	}
	else
	{
		newNode = new DoubleNode<Type>(data, nullptr, head());
		head() -> previous = newNode;
		head_of_list = newNode;

	}
	++size_of_linkedlist;

}

//insert element at the end
template <class Type>
void DoublyLinkedList<Type>::push_back(const Type &data) 
{
	DoubleNode<Type> *newNode;
	if (empty())
	{
		newNode = new DoubleNode<Type>(data, nullptr, nullptr);
		head_of_list = tail_of_list = newNode;

	}
	else
	{
		newNode = new DoubleNode<Type>(data, tail(), nullptr);
		tail()->next = newNode;
		tail_of_list = newNode;

	}
	++size_of_linkedlist;

}

//remove element from beginning
template <class Type>
Type DoublyLinkedList<Type>::pop_front() 
{	
	//Throw an underow exception if the list is empty.
	if (empty())
	{
		throw underflow_error("empty list, there is no node left to delete.");
	}

	//Delete the node at the front of the linked list and, as necessary, 
	//update the head and tail pointers.Return the object stored in the node being popped.

	if (size_of_linkedlist == 1)
	{
		Type node_popped = front();

		DoubleNode<Type> * ptr = head();
		head_of_list = tail_of_list = nullptr;
		delete ptr;
		--size_of_linkedlist;
		return node_popped;

	}
	else
	{
		Type node_popped = front();
		DoubleNode<Type> *ptr = head();
		head_of_list = head_of_list->getNext();
		head_of_list->previous = nullptr;
		delete ptr;
		--size_of_linkedlist;
		return node_popped;
	}
}

//Delete the node(s) (from the front) in the linked list that contains the element 
//equal to the argument(use == to to test for equality with the retrieved element).
//As necessary, update the head and tail pointers and the next pointer of any other
//node within the list. Return the number of nodes that were deleted.
template <class Type>
int DoublyLinkedList<Type>::erase(const Type &key) 
{	
    if (empty())
    {
        throw underflow_error("List is empty");
    }
	int count = 0;
	//iterating through the list to find and delete
	for(DoubleNode<Type> * ptr = head_of_list; ptr != nullptr; ptr = ptr->getNext())
	{
		if(ptr -> getData() == key)
		{
			//if key found at the head, call pop_front for deletion
			if(head() == ptr)
			{
				pop_front();
			}
			//if found at tail, call pop_ball for deletion
			else if(tail()==ptr)
			{		
				//pop_back();
				if(empty())
				{
					throw underflow_error("List is empty, there is no element left to delete.");
				}

				// if list size is 1, set head and tail pointers to nullptr, return popped value
				if(size_of_linkedlist == 1)
				{
					Type node_popped = back();

					DoubleNode <Type> * ptr = tail();
					tail_of_list = head_of_list = nullptr;
					delete ptr;
					--size_of_linkedlist;
					

				}
				// if list size > 1, set head and tail to nullptr, return popped value.
				else
				{
					Type node_popped = back();
					DoubleNode <Type> *ptr = tail();
					tail_of_list = tail_of_list -> getPrevious();
					tail_of_list -> next = nullptr;
					delete ptr;
					--size_of_linkedlist;

				}
			}

			// if found somewhere between head and tail.
			else
			{
				ptr -> previous -> next = ptr -> next;
				ptr -> next -> previous = ptr -> previous;
				delete ptr;
				--size_of_linkedlist;
				//DoublyLinkedList::printlst();
			}
			++count;
		}
	}
	return count;
}

//print the list
template <class Type>
void DoublyLinkedList<Type>::printlst() const
{
        if (empty())
        {
            throw underflow_error("List is empty");
        }
		DoubleNode<Type> *ptr = head_of_list;
        for (int i = 0; i < size_of_linkedlist;i++)
		{
			cout << "Node[" << i <<"]= " << ptr->data << "-->";
			ptr = ptr -> next;
		}

        cout << "0" << endl;
}


