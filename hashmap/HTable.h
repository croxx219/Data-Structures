#pragma once
#include <string>
#include "SLinkedList.h"

static const double loadfactor = 0.73;   // Approximately 19 entries with 26 buckets.


template <typename kType, class myType>
class HTable {
private:
    int totalElements;
    int entries;
    int capacity;
    SLinkedList<myType> *listArray;
  
    int getIndex(const string & key);
    int getIndex(const int & key);
    int getIndex(const char & key);
  
    /* Returns index to a bucket in the hash table*/
    // This is the "hash function"

public:  
    /*int getIndex(const string & key);
    int getIndex(const int & key);
    int getIndex(const char & key);*/
    HTable(int c = 26) :totalElements(0),entries(0) {
        this->capacity = c;
        listArray = new SLinkedList<myType>[capacity];
        cout << "Created with capacity " << capacity << endl;
    }
    
    bool isEmpty() const {
        return totalElements == 0;
    }

    bool isEmpty(const kType & key) {
        int idx = HTable::getIndex(key);
        return listArray[idx].empty();
    }

    int getSize() const {
        return totalElements;
    }

    int getEntries() const {
        return entries;
    }


    int getCapacity() const {
        return capacity;
    }
    
    // Since the push_back function is being used for insertion, collision treatment happens automatically.
    void insert(const kType & key, const myType & value) {
        int idx = HTable::getIndex(key);
        
        if (this->isEmpty(key))
            entries++;
       
        if (((double)entries / capacity) >= loadfactor) {
            capacity *= 2;
            SLinkedList<myType> *tmpArray = new SLinkedList<myType>[capacity];
            for (int i = 0; i <= capacity/2;i++)
                tmpArray[i] = listArray[i];
            delete[] listArray;
            listArray = tmpArray;
        }
        
        listArray[idx].push_back(value);
        totalElements++;
    }
   
    void delValues(const kType & key) {
        int idx = HTable::getIndex(key);
        int delNodes;
        if (!listArray[idx].empty())
            delNodes = listArray[idx].clear();

        if (delNodes == 0) cout << "Location is empty" << endl;
        else cout << delNodes << " elements erased" << endl;

        totalElements -= delNodes;
        --entries;
    }

    void search(const kType & key) {
        int i = HTable::getIndex(key);
        if (!HTable::isEmpty(key)) {
            listArray[i].printList();
        }
        else 
            cerr << "Position is empty";
    }

    void printTable() const {
        for (int i = 0;i < capacity;i++) {
            if (listArray[i].empty()) continue;
            cout << "Entry " << i << " > ";
            listArray[i].printList();
        }
    }

    ~HTable() {
        delete[] listArray;
        totalElements = entries = capacity = 0;
        cout << "Destructor called" << endl;
    }
};

template<>
int HTable<string, string>::getIndex(const string & key) {
    int hash = tolower(key[0]) % 97;
    int idx = hash%capacity;
    //cout <<"index->" << idx << endl;
    return idx;
};

template<>
int HTable<int, string>::getIndex(const int & key) {
    int hash = key % 97;
    int idx = hash%capacity;
    //cout <<"index->" << idx << endl;
    return idx;
};

template<>
int HTable<int,string>::getIndex(const char & key) {
    int hash = tolower(key) % 97;
    int idx = hash%capacity;
    //cout <<"index->" << idx << endl;
    return idx;
};

