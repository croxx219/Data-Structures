#include <iostream>
using namespace std;

#define PARENT_IDX(i) (i/2)
#define LEFT_IDX(i) (2*i)
#define RIGHT_IDX(i)((2*i)+1)

template<class type>
class treeNode 
{
private:
	type data;
	int key;
	treeNode<type> * parent;
	treeNode<type> * left;
	treeNode<type> * right;
	//template<class U> friend class maxHeap;

public:

	treeNode(int key, type data) :key(0), parent(0), left(0), right(0)
	{
		this->key = key;
		this->data = data;
	}

	int getKey() const{ return key;}

	type getData() const { return data; }

	treeNode<type> * getParent() { return parent; }

	treeNode<type> * getLeft() { return left; }

	treeNode<type> * getRight() { return right; }

};
