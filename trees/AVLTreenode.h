#pragma once
#include <iostream>

using namespace std;

template<class Type> class treenode{
	private:
		//Type data;
		int key;
		Type data;
		treenode<Type> * parent;
		treenode<Type> * lChild;
		treenode<Type> * rChild;
		template<class U> friend class AVLTree;
	public:
		int balance;
		treenode(const int & key, const Type & data):parent(nullptr),lChild(nullptr),rChild(nullptr),balance(0){
			this->key = key;
			this->data = data;
		}
		~treenode(){
		//	cout << "Node " << this->key << " is being deleted" << endl;
		}
		int getKey() const{
			return key;
		}
		void insertKey(int key){
			this->key = key;
		}
		Type getData() const{
			return data;
		}
		void insertData(const Type & data){
			this->data = data;
		}
		treenode<Type> * getParent() const{
			return parent;
		}
		treenode<Type> * getLChild() const{
			return lChild;
		}
		treenode<Type> * getRChild() const{
			return rChild;
		}
};