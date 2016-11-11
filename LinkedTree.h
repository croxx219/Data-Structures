#pragma once
#include "TreeNode.h"
#include "mQueue.h"
#include <string>
#include <fstream>

template <class Type>
class LinkedTree {
private:
    TreeNode<Type> * root;
    int size;

    TreeNode<Type> * nextSibling(TreeNode<Type> * treeNode) {
        if (treeNode->parent != NULL) {
            Node<TreeNode<Type> * > *ptr = treeNode->parent->children->leftChild;
            while (ptr->data->getData() != treeNode->getData() && ptr->next != NULL) {
                ptr = ptr->next;
            }
            if (ptr->next == NULL) {
                return NULL;
            }
            return ptr->next->data;
        }
        else
            return 0;
    }

    Node<TreeNode<Type>*> *nextLNode(TreeNode<Type> * treeNode) {
        if (treeNode->parent != NULL) {
            Node<TreeNode<Type> * > *ptr = treeNode->parent->children->leftChild;
            while (ptr->data->getData() != treeNode->getData() && ptr->next != NULL) {
                ptr = ptr->next;
            }
            if (ptr->next == NULL) {
                return NULL;
            }
            return ptr->next;
        }
        else
            return 0;
    }

    void visit(TreeNode<Type> *ptr) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        cout << ptr->data << endl;
    }
   
    TreeNode<Type> * findParent(string str) {
        int level = 0;
        for (int i = str.size() - 1;i >= 0;i--) {
            if (str[i] == '.') {
                level++;
            }
        }
        if (level < 1) return root;
        else {
            int last_dot = str.find_last_of('.');
            int cur_level = 0;
            str = str.substr(last_dot + 1); // 0.#.#.par_pos
            string::size_type sz;
            int par_pos = stoi(str, &sz);
            TreeNode<Type> * ptr = root;
            while (!ptr->children->isEmpty() && cur_level != level) {
                ptr = ptr->children->leftChild->data;
                cur_level++;
            }
            for (int i = 0;i < par_pos;i++) {
                ptr = nextSibling(ptr);
            }
            return ptr;
        }
    }


    TreeNode<Type> * find(const Type & data, TreeNode<Type> * ptr) {
        if (ptr->data == data) {
            return ptr;
        }
        TreeNode<Type> * tmp1 = NULL;
        TreeNode<Type> * tmp2 = NULL;
        if (ptr->children->leftChild != NULL)
            tmp1 = find(data, ptr->children->leftChild->data);
        if (nextSibling(ptr) != NULL) {
            tmp2 = find(data, nextSibling(ptr));
        }

        return tmp1 != NULL ? tmp1 : tmp2;

    }
   
public:
    LinkedTree() : root(0), size(0) {}

    void build_tree(string path) {
        string line;
        ifstream myfile(path);
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                int pos = line.find(' ');
                string data = line.substr(0, pos);
                string str = line.substr(pos + 1);
                pos = str.find_last_of('.');
                string str2 = str.substr(pos + 1);
                string::size_type sz;
                int node_pos = stoi(str2, &sz);
                str = str.substr(0, pos);
                TreeNode<Type> *ptr = findParent(str);  // Issue starts here @ 0
                insert(data, ptr, node_pos);  // This is fine
            }
            myfile.close();
        }
        else cout << "Unable to open file";
    }

    void insert(const Type & data, TreeNode<Type> *parent, int node_pos) {
        cout << "Inserting " << data << " in position " << node_pos << ", parent is " << (parent == NULL ? "NULL, this is the root." : parent->data) << endl;
            
        TreeNode<Type> *n = new TreeNode<Type>(data);
            
        if (parent == NULL) {
            root = n;
            root->key = node_pos;
            size++;
        }
        else {
            n->parent = parent;
            n->key = node_pos;
            parent->children->insert(n);
            size++;
        }      
    }

    TreeNode<Type> * getRoot() const { 
        if (root == NULL)
            throw underflow_error("Root is NULL");
        return root; 
    }
    
    int getHeight() { return getHeight(root); }
    
    int getSize() { return size; }
    
    bool empty() { return root == NULL; }
    
    int siblings(TreeNode<Type> * ptr) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        return ptr->parent->children->getSize()-1;  // Returns size of the list of children
    };
    
    int getDepth(TreeNode<Type> * node) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        if (node == root)
            return 0;
        else {
            return  1 + getDepth(node->parent);
        }
    }
   
    void clear() {
        delete root->children;
        root = NULL;
        size = 0;
    }

    // This methods returns height of the tree + 1, compensated in menu call.
    int getHeight(TreeNode<Type> * node) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        if (node == NULL) return 0;
        int max = 0;
        int h = 0;
        if (node->children->leftChild != NULL)
            h = getHeight(node->children->leftChild->data);
        if (h > max) {
            max = h;
        }
        max = max + 1;
        if (nextSibling(node) != NULL)
            h = getHeight(nextSibling(node));
        if (h > max) {
            max = h;
        }
        return max;
    }

    int leaves(TreeNode<Type> * treeNode) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        int count = 0;
        cout << treeNode->data << endl;
        if (treeNode->children->isEmpty()) {
            count++;
        }
        if (treeNode->children->leftChild != NULL)
             count += leaves(treeNode->children->leftChild->data);
        if (nextSibling(treeNode) != NULL) {
            count  += leaves(nextSibling(treeNode));
        }

        return count;
    }

    void del(Type const & data) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        TreeNode<Type> * delNode = findNode(data);
        // Has no child, has no sibling.
        if (delNode->children->leftChild == NULL && nextLNode(delNode) == NULL) {
            delNode->parent->children->del(delNode);
            size--;
        }
        // Has child, has sibling (including NULL sibling)
        else if (delNode->children->leftChild != NULL) {
            delNode->data = delNode->children->leftChild->data->data;
            delNode->children->del(delNode->children->leftChild->data);
            size--;
        }
        // Has no child, has sibling
        else if (nextLNode(delNode) != NULL) {
           delNode->parent->children->del(delNode);
           size--;
        }
    }

    TreeNode<Type> * findCommonAncestor(TreeNode<Type>  * node1, TreeNode<Type> * node2) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        int d1 = getDepth(node1);
        int d2 = getDepth(node2);
        while (d1 != d2) {
            if (d1 > d2) {
                node1 = node1->parent;
                --d1;
            }
            else {
                node2 = node2->parent;
                --d2;
            }
        }
        if (node1->data == node2->data) 
            return node1;
        else 
            if ((node1->parent == NULL) || (node2->parent == NULL))
                return root;
            else {
                if (node1->parent->data == node2->parent->data) {
                    return node1->parent;
                }
                else findCommonAncestor(node1->parent, node2->parent);
            }
        

    }

    TreeNode<Type> *findNode(const Type & data) {
        if (root == NULL) return NULL;
        else {
            TreeNode<Type> * result = find(data, root);
            if (result == NULL)
                throw underflow_error("Node not found");
            else return result;
        }
    }


    void preorder(TreeNode<Type> *ptr) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        this->visit(ptr);
        if (ptr->children->leftChild != NULL) {
            preorder(ptr->children->leftChild->data);
        }
        if (nextLNode(ptr) != NULL) {
            preorder(nextSibling(ptr));
        }
    }

    void postorder(TreeNode<Type> *ptr) {
        if (root == NULL)
            throw underflow_error("Root is NULL");
        if (ptr->children->leftChild != NULL) {
            postorder(ptr->children->leftChild->data);
        }
        this->visit(ptr);
        if (nextLNode(ptr) != NULL) {
            postorder(nextSibling(ptr));
        }
    }

    void levelorder(TreeNode<Type> *ptr) {
        if (root == NULL)
            throw underflow_error("Root is NULL");

        int curlevel = 1;
        int nextlevel = 0;

        mQueue<TreeNode<Type>*> *queue = new mQueue<TreeNode<Type>*>();
        queue->enqueue(ptr);

        while (!queue->isEmpty()) {
            TreeNode<Type> * tmp = queue->dequeue();

            // This is used to format output
            if (curlevel == 0) {
                cout << endl;
                curlevel = nextlevel;
                nextlevel = 0;
            }
            
            // Add every child into the queue
            TreeNode<Type> *n = tmp;
            if (n->children->leftChild != NULL) {
                queue->enqueue(n->children->leftChild->data);
                nextlevel++;
                n = n->children->leftChild->data;
                while (nextLNode(n) != NULL) {
                        queue->enqueue(nextSibling(n));
                        nextlevel++;
                        n = nextSibling(n);
                }
            }

            curlevel--;
            cout << tmp->data << " ";
            
        }
        cout << endl;
    }

    ~LinkedTree() {
        delete root;
        size = 0;
    }
   

};