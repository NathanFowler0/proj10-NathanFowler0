/* BST.h declares a "classic" binary search tree of linked nodes.
 * Joel Adams, for CS 112 at Calvin University.
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>

#include "Exception.h"
using namespace std;

template <class Item>
class BST {
public:

    /****************************
     * start of project 10 code *
     ****************************/

    unsigned getHeight() const;

    /**************************
     * end of project 10 code *
     **************************/
    BST();
    virtual ~BST();
    bool isEmpty() const;
    unsigned getNumItems() const;
    void traversePreorder() const;
    void traversePostorder() const;
    void traverseInorder() const;
    void insert(const Item& it);
    bool contains(const Item& it) const;

    // This stuff below should be private: but because
    // we need to access it for testing, we leave it as public.
public:
    struct Node {
        /****************************
         * start of project 10 code *
         ****************************/

        unsigned getHeight() const;

        /**************************
         * end of project 10 code *
         **************************/

        Node(const Item& it);
        virtual ~Node();
        bool insert(const Item& it);
        bool contains(const Item& it) const;

        void traversePreorder() const;
        void traversePostorder() const;
        void traverseInorder() const;
        virtual void processItem() const;

        Item myItem;
        Node* myLeft;
        Node* myRight;
    };

    Node* myRoot;
    unsigned myNumItems;
};

/****************************
* start of project 10 code *
****************************/

template <class Item>
unsigned BST<Item>::getHeight() const {
    if (myRoot == nullptr) return 0;
    return myRoot->getHeight();
}

template <class Item>
unsigned BST<Item>::Node::getHeight() const {
    int leftHeight = 0, rightHeight = 0;
    if (myLeft != nullptr) leftHeight = myLeft->getHeight();
    if (myRight != nullptr) rightHeight = myRight->getHeight();
    return 1 + (leftHeight < rightHeight ? rightHeight : leftHeight);
}

/**************************
 * end of project 10 code *
 **************************/

template <class Item>
BST<Item>::BST() {
    myRoot = nullptr;
    myNumItems = 0;
}

template <class Item>
BST<Item>::~BST() {
    delete myRoot;
}

template <class Item>
BST<Item>::Node::Node(const Item& it) {
    myItem = it;
    myLeft = nullptr;
    myRight = nullptr;
}

template <class Item>
void BST<Item>::Node::processItem() const {
    cout << ' ' << myItem;
}

template <class Item>
BST<Item>::Node::~Node() {
    delete myLeft;
    delete myRight;
}

template <class Item>
bool BST<Item>::isEmpty() const {
    return myNumItems == 0;
}

template <class Item>
unsigned BST<Item>::getNumItems() const {
    return myNumItems;
}

template <class Item>
void BST<Item>::traversePreorder() const {
    if (!isEmpty()) {
        myRoot->traversePreorder();
    }
}

template <class Item>
void BST<Item>::insert(const Item& it) {
    bool isNew = true;
    if (myRoot == nullptr) {
        myRoot = new Node(it);
    }
    else {
        isNew = myRoot->insert(it);
    }
    if (isNew) {
        myNumItems++;
    }
    else {
        throw Exception("insert()", "item is already in tree");
    }
}

template <class Item>
bool BST<Item>::Node::insert(const Item& it) {
    if (myItem == it) {
        return false;
    }
    if (it < myItem) {
        if (myLeft == nullptr) {
            myLeft = new Node(it);
            return true;
        }
        else {
            return myLeft->insert(it);
        }
    }
    else {
        if (myRight == nullptr) {
            myRight = new Node(it);
            return true;
        }
        else {
            return myRight->insert(it);
        }
    }
}

template <class Item>
bool BST<Item>::contains(const Item& it) const {
    if (myRoot == nullptr) return false;
    return myRoot->contains(it);
}

template <class Item>
bool BST<Item>::Node::contains(const Item& it) const {
    if (myItem == it) return true;
    else if (it < myItem) {
        if (myLeft == nullptr) return false;
        return myLeft->contains(it);
    }
    else {
        if (myRight == nullptr) return false;
        return (myRight->contains(it));
    }
}

template <class Item>
void BST<Item>::Node::traversePreorder() const {
    // 1. process myItem first (preorder)
    processItem();
    // 2. then recursively process the items in the left subtree
    if (myLeft != nullptr) {
        myLeft->traversePreorder();
    }
    // 3. then recursively process the items in the right subtree
    if (myRight != nullptr) {
        myRight->traversePreorder();
    }
}

template <class Item>
void BST<Item>::traversePostorder() const {
    if (!isEmpty()) {
        myRoot->traversePostorder();
    }
}

template <class Item>
void BST<Item>::traverseInorder() const {
    if (!isEmpty()) {
        myRoot->traverseInorder();
    }
}

template <class Item>
void BST<Item>::Node::traversePostorder() const {

    // 1. first recursively process the items in the left subtree
    if (myLeft != nullptr) {
        myLeft->traversePostorder();
    }
    // 2. then recursively process the items in the right subtree
    if (myRight != nullptr) {
        myRight->traversePostorder();
    }

    // 3. then process myItem 
    processItem();
}

template <class Item>
void BST<Item>::Node::traverseInorder() const {
    // 1. first recursively process the items in the left subtree
    if (myLeft != nullptr) {
        myLeft->traverseInorder();
    }

    // 2. then process myItem 
    processItem();

    // 3. then recursively process the items in the right subtree
    if (myRight != nullptr) {
        myRight->traverseInorder();
    }
}

#endif /*BST_H_*/
