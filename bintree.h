// ------------------------------------------------ bintree.h -------------------------------------------------------
// Karan Kumar CSS 343
// 4/19/24
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Create a binary search tree class called Bintree that has some additional functions.
// Has a default and copy constructor and destructor. Overloaded =, ==, and != operators. Overloaded << to display tree
// with inorder traversal. Can retrieve NodeData, get height, make tree empty and insert nodes.
// Can also convert tree to array, and convert array to tree.
// --------------------------------------------------------------------------------------------------------------------
// Input ends with $$ and is used to construct a separate binary tree, duplicates ignored. Inorder traversal is used
// to display the tree and convert it to array.
// --------------------------------------------------------------------------------------------------------------------

#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

//function descriptions in .cpp file
class BinTree
{
    // overloaded print operator
    friend ostream &operator<<(ostream &out, const BinTree &b);

private:
    struct Node
    {
        NodeData *data; // pointer to data
        Node *left;
        Node *right;
    };
    Node *root; // pointer to root

public:
    // constructors and destructor
    BinTree();
    BinTree(const BinTree &other);
    void copyHelper(Node *node);
    ~BinTree();
    void destructorHelper(Node *node);
 
    // operator overloading
    BinTree &operator=(const BinTree &other);
    bool operator==(const BinTree &other) const;
    bool equalityHelper(Node *left, Node *right) const;
    bool operator!=(const BinTree &other) const;

    // additional functions
    bool retrieve(const NodeData &, NodeData *&);
    Node *retrieveHelper(Node *node, const NodeData &data, NodeData *&p);
    int getHeight(const NodeData &);
    int heightHelper(Node *&, const NodeData &, int &);
    void bstreeToArray(NodeData *[]);
    void bstreeToArrayHelper(Node *node, NodeData *arr[], int &i);
    void arrayToBSTree(NodeData *[]);
    void arrayToBSTreeHelper(Node *node, NodeData *arr[], int s, int e);
    void sideways(Node *node, int level) const;
    void displaySideways() const;
    bool isEmpty() const;
    void makeEmpty();
    bool insert(NodeData *data);
    void printer(const Node *node) const;
};
#endif