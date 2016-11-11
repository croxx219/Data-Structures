#pragma once
#include "SingleNode.h"

template<class Type>
class DoubleNode
{
private:
	//Data Members
	Type data; //Type variable that contains the data information of the node.
	DoubleNode* previous; // A pointer to a DoubleNode object, referred to as the next pointer.
	DoubleNode* next; // A pointer to a DoubleNode object, referred to as the previous pointer.
	//int ID;
    template<class Type>
    friend class DoublyLinkedList;
public:
	//Constructor
	/*This constructor takes three arguments: a constant reference to an Type (by
	default, an integer) and two pointers to a DoubleNode (each by default nullptr).
	These are assigned to the member variables, respectively.*/
	DoubleNode (Type const& = Type(), DoubleNode* = nullptr, DoubleNode* = nullptr);

	//Accessor
	Type getData()const;
	DoubleNode *getPrevious()const;
	DoubleNode *getNext() const;

	//Friends
	//This DoublyLinkedList< Type > is a friend of this class.
	friend class DoublyLinkedList<Type>;

	//Mutators
	//This class has no mutators.

	//Destructor
	~DoubleNode() {}

};

template<class Type>
DoubleNode<Type>::DoubleNode(Type const &d, DoubleNode<Type> *p, DoubleNode<Type> *n):
	data(d), previous(p), next(n)
	{
		//ID = num++;
	}

//Returns the element of the node.
template<class Type>
Type DoubleNode<Type>::getData()const
{
		return data;
}

//Returns the previous pointer.
template<class Type>
DoubleNode<Type>*DoubleNode<Type>::getPrevious()const
{
	if (previous == nullptr)
	{
		return nullptr;
	}
	else
	{
		return previous;
	}

}

//Returns the next pointer.
template<class Type>
DoubleNode<Type>*DoubleNode<Type>::getNext()const
{
	if (next == nullptr)
	{
		return nullptr;
	}
	else
	{
		return next;
	}

}
