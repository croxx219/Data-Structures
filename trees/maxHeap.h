#include <fstream>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include "heapTreeNode.h"

using namespace std;
template <class type> 
class maxHeap 
{
private:
	treeNode<type> * root;
	treeNode<type> ** heapArray;
	int size;
	int default_capacity;
	int height;
	treeNode<type> * treenode;
	int num_of_leaves;

public:

//Accessors 

	//constructor
	maxHeap(int c = 64): size(0), root(0)
	{
		this->default_capacity = c;
		heapArray = new treeNode<type>*[default_capacity];
		cout << "Created with capacity " <<default_capacity << endl;
	}

	//destuctor
	~maxHeap();

	treeNode<type> * getMax(); 

	int getSize() const;

	int getHeight() const;

	int getCapacity() const;

	treeNode<type> * getRoot();

	bool empty();

	int leaves() const;


//Mutators	
	void buildTree();

	void parseLine(string line, int & key, string & data);

	void clear();
	
	void swaps(treeNode<type> *a, treeNode<type> *b);

	void insert(int key, const type & data); 

	void delMax();

	void Heapify(int idx);

	void Print();

};


template<class type>
maxHeap<type>::~maxHeap() 
{
	delete[] heapArray;
	size = 0;
	cout<< " Destructor called"<<endl;

}

//returns the max/root of the tree, max will always be on index 1
template<class type>
treeNode<type>* maxHeap<type>::getMax() 
{ 
	if (empty())
	{
		throw underflow_error("heap is empty");
	}

	return heapArray[1]; 
}

//returns the number of elements in the tree
template<class type>
int maxHeap<type>:: getSize() const
{ 
	return size; 
}

//testing
template<class type>
treeNode<type> * maxHeap<type>::getRoot()
{
	return root;
}

template<class type>
int maxHeap<type>:: getCapacity() const
{
	return default_capacity;
}

//returns the height of the tree
//complete binary tree of n node has height of floor(log2(n))
template<class type>
int maxHeap<type>:: getHeight() const
{
	if(size == 0)
	{
		return 0;
	}
	else
	{
		return floor(log2(size));
	}

}

//return tree is empty
template<class type>
bool maxHeap<type>::empty() 
{ 
	return size == 0; 
}

// returns the number of leaves in the tree
template<class type>
int maxHeap<type>::leaves() const
{

	return (size +1) /2 ;
}

template<class type>
void maxHeap<type>::swaps(treeNode<type> *a, treeNode<type> *b)
{
    treeNode<type> *tempArray = a;
    a = b;
    b = tempArray;
}

//remove all the elements in the tree
template<class type>
void maxHeap<type>::clear() 
{
	delete heapArray;
	heapArray = new treeNode<type>*[default_capacity];
	size = 0;
}

//insert data in the tree, must satisfied the heap property
template<class type>
void maxHeap<type>::insert(int key, const type & data) 
{
	//If an entry is being inserted, and the array is already full 
	if (size == default_capacity - 1) 
	{
		int key = 0;
		type data;

		//the capacity of the array is doubled.
		treeNode<type> **tempArray = new treeNode<type>*[default_capacity * 2];
		for (int i = 0; i < default_capacity * 2; i++) 
		{
			tempArray[i] = new treeNode<type>(key, data);
		}
		for (int i = 0; i < size; i++) 
		{
			tempArray[i] = heapArray[i];
		}
		*heapArray = *tempArray;
		delete[] tempArray;
	}
	treenode = new treeNode<type>(key, data);
	size++;
	heapArray[size] = treenode;
	Heapify(size); 
}

//read stuctures from a text file and builds a max heap
template<class type>
void maxHeap<type>::buildTree()
{
	string line;
	ifstream myfile("heaptree.txt");
	if (myfile.is_open())
	{
		cout<<"file opened"<<endl;
		string data;
		int key;
		while (getline(myfile, line))
		{
			parseLine(line, key, data);
			insert(key, data);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

template<class type>
void maxHeap<type>::parseLine(string line, int & key, string & data) 
{
	string::size_type sz;
	int pos = line.find(' ');
	string k = line.substr(0, pos);
	data = line.substr(pos + 1);
	key = stoi(k, &sz);
}

//removes the entry specified by maximun key in the tree
//must satisfied  the heap property
template<class type>
void maxHeap<type>::delMax() 
{
	if (empty())
	{
		throw underflow_error("empty, nothing to delete");
	}

	//if, after removing an entry from the heap, 
	//and the number of entries is one - quarter the capacity of the array, 
	if (size == (default_capacity * 0.25)) 
	{
		int key = 0;
		type data;

		//then the capacity of the array is halved.
		treeNode<type> **tempArray = new treeNode<type> *[default_capacity / 2];
		for (int i = 0; i < (default_capacity/2); i++) 
		{
			tempArray[i] = new treeNode<type>(key, data);
		}
		for (int i = 0; i < size; i++) 
		{
			tempArray[i] = heapArray[i];
		}
		*heapArray = *tempArray;
		delete[] tempArray;
	}
	heapArray[1] = heapArray[size]; 
	int x = size;
	while (x > 0) { Heapify(x); --x; }
	--size; 
}

//heapify the tree to maintaining the heap property
template<class type>
void maxHeap<type>:: Heapify(int idx) 
{
	int parent = PARENT_IDX(idx);
	int left = idx - 1;

	if (idx > 1) 
	{
		if (idx % 2 == 0) 
		{ 
			if (heapArray[idx]->getKey() > heapArray[parent]->getKey()) 
			{
				swap(heapArray[idx], heapArray[parent]);
			}
		}
		else 
		{ 
			if (heapArray[idx]->getKey() > heapArray[parent]->getKey()) 
			{
				swap(heapArray[idx], heapArray[parent]);

			} 
			if (heapArray[left] != nullptr) 
			{
				if (heapArray[left]->getKey() < heapArray[idx]->getKey()) 
				{
					swap(heapArray[idx], heapArray[left]);
				}
			}
		}
	}
		if (parent > 1) { Heapify(parent); }
}

//print
template<class type>
void maxHeap<type>::Print() 
{
	if (empty()) 
	{
		throw underflow_error("empty, nothing to print");
	}
	for (int i = 1; i <= size; i++) 
	{
		cout << heapArray[i]->getKey() << " "; 
		cout << heapArray[i]->getData() << endl;
	}
	cout <<endl<<endl;
}

/*int leftChild(int parentIndex)
{
	return parentIndex * 2 + 1;
}

int rightChild(int parentIndex)
{
	return parentIndex * 2 + 2;
}

int parentIndex(int childIndex)
{
	return (childIndex - 1) >> 1;
}

//method 2 testing
void heapify2(int index)
{
	int max = index;
	int left = (2 * index) + 1;
	int right = (2 * index) + 2;

	if (left <= size && heapArray[left]->getKey() > heapArray[max]->getKey())
	{
		max = left;
	}

	if (right <= size && heapArray[right]->getKey() > heapArray[max]->getKey())
	{
		max = right;
	}
	if (max != index)
	{
		treeNode<type> * tempArray = heapArray[index]->getKey();
		heapArray[index]->setKey(heapArray[max]->getKey());
		heapArray[max]->setKey(tempArray);
		heapify2(max);
	}
}


*/

