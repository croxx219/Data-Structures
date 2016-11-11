#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cmath>
#include "AVLTreenode.h"
#include "mQueue.h"

template<class Type> class AVLTree{
private:
	int size;				//number of elements
	int depth;				//depth of the tree
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

public:
	treenode<Type> *root = nullptr;
	AVLTree():root(nullptr),size(0),depth(0){}
	~AVLTree(){};

	//Accessors
	treenode<Type> * getRoot()const{
		if(root == nullptr) throw underflow_error("nullptr");
		return root;
	}
	int getSize()const{
		return size;
	}
	int getHeight()const{
		if(root == nullptr) throw underflow_error("0");
		int height = (log2(getSize())+1);
		return height;
	}
	int getHeight(treenode<Type> *node)const{

		int left= 0, right=0;

     	if(node==nullptr){
     		return -1;
     	}
     		left = getHeight(node->lChild);
     		right = getHeight(node->rChild);
  		if(left > right){
            return left+1;
  		}
        else{
            return right+1;
        }
	}
	int getDepth(treenode<Type> * node)const{
		if(root == nullptr) throw underflow_error("0");
		int depth = 0;
		if(node == root){
			return 0;
		}
		else{
			depth =  1 + getDepth(node->parent);
		}
		return depth;
	}
	bool empty()const{
		return root == nullptr;
	}
	int leaves(treenode<Type> * node)const{
		if(root == nullptr) throw underflow_error("0");
		int count = 0;

		if (node->lChild == nullptr && node->rChild == nullptr){
            ++count;
        }    
		if (node->lChild != nullptr){
             count += leaves(node->lChild);
        }      
        
        if (node->rChild != nullptr){
           count += leaves(node->rChild);
        }
		return count;
	}

	int siblings(treenode<Type> *node)const{
		int siblings = 0;
		if(node->parent->lChild && node->parent->rChild){
			siblings = 1;
			return siblings;
		}	

		return siblings;
	}
//*************Can't Validate Data Entry matches key ******************
	treenode<Type> *find(int const & key, Type const & data){
		if(root == nullptr) throw underflow_error("Empty Tree");
		treenode<Type> * ptr = root;
		int count = 0;

		if(ptr->key == key) {
			return ptr;
		}
		while(ptr->key != key){
				if(key <= ptr->key){
				ptr = ptr->lChild;
			}
			else{
				ptr = ptr->rChild;
			}
			count++;
			if(ptr == nullptr){
				throw underflow_error("Key not found");
			}
		}
/*		if(ptr->data != data){
			cout << "ptr->data " << ptr->data << endl;
			throw underflow_error("Data not found");
		}
		else*/
		return ptr;
	}

	void preorder(treenode<Type> *node)const {
		if(node == nullptr) return;
		cout << node->key << " ";
		//cout << node->data << " ";
		preorder(node->lChild);
		preorder(node->rChild);
	}

	void postorder(treenode<Type> *root)const {
		if(root == nullptr) return;
		postorder(root->lChild);
		postorder(root->rChild);
		cout << root->key << " ";
	}

	void levelorder(treenode<Type> *node)const {
		if (root == nullptr)
            throw underflow_error("Root is nullptr");

        int curlevel = 1;
        int nextlevel = 0;

        mQueue<treenode<Type>*> *queue = new mQueue<treenode<Type>*>();
        treenode<Type> * tmp = root;
        while(tmp){
        	cout << tmp->key << " ";
            
            if (curlevel == 0) {
                cout << endl;
                curlevel = nextlevel;
                nextlevel = 0;
            }
           		if(tmp->lChild)
           			queue->enqueue(tmp->lChild);
           		if(tmp->rChild)
           			queue->enqueue(tmp->rChild);
				tmp = queue->dequeue();       	
        }
	}

	void inorder(treenode<Type> *root)const{
		if(root == nullptr) return;

		inorder(root->lChild);
		cout << root->key << " ";
		inorder(root->rChild);
	}

	//mutators

	void buildTree()
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
	void parseLine(string line, int & key, string & data) 
	{
		string::size_type sz;
		int pos = line.find(' ');
		string k = line.substr(0, pos);
		data = line.substr(pos + 1);
		key = stoi(k, &sz);
	}

	void clear(){
		if(root == nullptr) throw underflow_error("Already empty");
		delete root->lChild;
		delete root->rChild;
		root = nullptr;
		size = 0;
	}

	bool insert(int const & key,Type const & data) {
	    if (root == nullptr) {
	        root = new treenode<Type>(key, data);
	        size++;
	    }
	    else {
	        treenode<Type> *n = root;
	        treenode<Type> *parent;
	 
	        while (true) {
	            if (n->key == key)
	               return false;
	 
	            parent = n;
	 
	            bool goLeft = n->key > key;
	            n = goLeft ? n->lChild : n->rChild;
	 
	            if (n == nullptr) {
	            	treenode<Type> * Child = new treenode<Type>(key, data);
	                if (goLeft) {
	                    parent->lChild = Child;
	                    size++;
	                }
	                else {
	                    parent->rChild = Child;
	                    size++;
	                }
 					Child->parent = parent;
    	            rebalance(parent);
    	            break;
    	        }
    	    }
    	}
 	
 	   return true;
	}	

	void del(int const & key) {
	    if (root == nullptr) return;
	 
	    treenode<Type> *n = root;
	    treenode<Type> *parent = root;
	    treenode<Type> *delNode = nullptr;
	    treenode<Type> *child = root;
 	
 	   while (child != nullptr) {
 	       parent = n;
 	       n = child;
 	       child = key >= n->key ? n->rChild : n->lChild;
 	       if (key == n->key)
 	           delNode = n;
    	}
 	
 	   if (delNode != nullptr) {
 	       delNode->key = n->key;
 
 	       child = n->lChild != nullptr ? n->lChild : n->rChild;
 	
    	    if (root->key == key) {
    	        root = child;
    	    }
    	    else {
    	        if (parent->lChild == n) {
    	            parent->lChild = child;
    	        }
    	        else {
    	            parent->rChild = child;
    	        }
 
	            rebalance(parent);
	            size--;
	        }
	    }
	}    	

	void rebalance(treenode<Type> *n) {
    setBalance(n);
    if (n->balance == -2) {
        if (getHeight(n->lChild->lChild) >= getHeight(n->lChild->rChild)){
            n = rotateRight(n);
        }
        else{
            n = rotateLeftThenRight(n);
        }
    }
    else if (n->balance >= 2) {
        if (getHeight(n->rChild->rChild) >= getHeight(n->rChild->lChild)){
            n = rotateLeft(n);
        }
        else{
            n = rotateRightThenLeft(n);
        }
    }
 
    if (n->parent != nullptr) {
        rebalance(n->parent);
    }
    else {
        root = n;
    	}
	}
	
	void setBalance(treenode<Type> *n) {
	    n->balance = getHeight(n->rChild) - getHeight(n->lChild);
	}

	treenode<Type> * rotateLeft(treenode<Type> *a) {
    treenode<Type> *b = a->rChild;
    b->parent = a->parent;
    a->rChild = b->lChild;
    if (a->rChild != nullptr)
        a->rChild->parent = a;
 
    b->lChild = a;
    a->parent = b;
 
    if (b->parent != nullptr) {
        if (b->parent->rChild == a) {
            b->parent->rChild = b;
        }
        else {
            b->parent->lChild = b;
        }
    }
 
    setBalance(a);
    setBalance(b);
    return b;
}
 
	treenode<Type>* rotateRight(treenode<Type> *a) {
	    treenode<Type> *b = a->lChild;
	    b->parent = a->parent;
	    a->lChild = b->rChild;
 
	    if (a->lChild!= nullptr)	
	        a->lChild->parent = a;
	 
	    b->rChild = a;
	    a->parent = b;
	 
	    if (b->parent != nullptr) {
	        if (b->parent->rChild == a) {
	            b->parent->rChild = b;
	        }
	        else {
	            b->parent->lChild = b;
	        }
	    }
	 
	    setBalance(a);
	    setBalance(b);
	    return b;
	}
 

	treenode<Type>* rotateLeftThenRight(treenode<Type> *n) {
    	n->lChild = rotateLeft(n->lChild);
    	return rotateRight(n);
	}
 

	treenode<Type>* rotateRightThenLeft(treenode<Type> *n) {
    	n->rChild = rotateRight(n->rChild);
    	return rotateLeft(n);
	}
};