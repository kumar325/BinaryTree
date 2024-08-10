// ------------------------------------------------ bintree.cpp -------------------------------------------------------
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
#include "bintree.h"

/**
 * Overloaded output operator
 * Outputs the contents of this tree to the provided ostream, in sorted order, space separated on a single line.
 * @pre The ostream out is writable.
 * @post Outputs the entire tree in inorder to the ostream and returns it, tree remains unchanged
 */
ostream &operator<<(ostream &out, const BinTree &b)
{
    b.printer(b.root);
    return out << endl;
}

/** Default Constructor
 * Creates an empty tree
 * @pre none
 * @post an empty BST now exists
 */
BinTree::BinTree() : root(nullptr)
{
}

/** Copy Constructor
 * Copies a BST from one tree into another
 * @pre There is sufficient memory to allocate a copy of orig.
 * @post A binary search tree exists that is a structural copy of the tree
 *       orig; orig remains unchanged.
 */
BinTree::BinTree(const BinTree &node) : root(nullptr)
{
    copyHelper(node.root);
}

/** Copy Helper
 * Recursively inserts all the nodes of the tree to copy
 * @pre An original binary search tree exists
 * @post A new binary search tree that is an exact copy of the original is created,
 * the original tree is unchanged
 */
void BinTree::copyHelper(Node *node)
{
    if (node)
    {
        NodeData *d = new NodeData(*node->data);
        insert(d);
        copyHelper(node->left);
        copyHelper(node->right);
    }
}

/** Destructor
 * Completely destroys binary search tree and frees up all memory
 * @pre A binary search tree exists
 * @post The tree is empty before memory is released,
 * all nodes and data within tree are deleted
 */
BinTree::~BinTree()
{
    destructorHelper(root);
}

/**
 * Destructor Helper
 * Recursively deletes all the nodes of the tree, bottom to top approach
 * @pre A binary search tree exists
 * @post The tree is empty before memory is released,
 * all nodes and data within tree are deleted
 */
void BinTree::destructorHelper(Node *node)
{
    if (node)
    {
        destructorHelper(node->left);
        destructorHelper(node->right);

        if (node->data)
        {
            delete node->data; // delete node data
            node->data = nullptr;
        }
        delete node; // delete node
        node = nullptr;
    }
    root = nullptr; // set root to null
}

/**
 * Overloaded equals operator
 * Copies content from other BST into current BST. Tree is cleared before copying.
 * @pre other the tree to be copied
 * @post tree is a copy of other, other is unchanged
 */
BinTree &BinTree::operator=(const BinTree &other)
{
    if (*this != other)
    {
        this->makeEmpty();
        root = nullptr;
        copyHelper(other.root);
    }
    return *this;
}

/**
 * Overloaded equality operator
 * Compares BST with other for equality (same data and tree structure)
 * @pre NodeData provides an equality operator.
 * @post both BST are unchanged
 */
bool BinTree::operator==(const BinTree &tree) const
{
    if (this->root == nullptr && tree.root == nullptr)
    {
        return true;
    }
    return equalityHelper(this->root, tree.root);
}

/**
 * Equality helper
 * Recursively compares each node of two binary trees to determine if they are equal.
 * @pre NodeData provides an equality operator.
 * @post trees are unchanged
 * Returns true if the subtrees rooted at the current nodes are equal in data and structure, otherwise false
 */
bool BinTree::equalityHelper(Node *left, Node *right) const
{
    if (!left && !right)
        return true;
    if (left && right)
    {
        return (
            *left->data == *right->data &&
            equalityHelper(left->left, right->left) &&
            equalityHelper(left->right, right->right));
    }
    return false;
}

/**
 * Overloaded inequality operator
 * Compares this BST with another for inequality (either data or tree structure differs)
 * @pre NodeData provides an equality operator.
 * @post both BSTs are unchanged
 */
bool BinTree::operator!=(const BinTree &tree) const
{
    return !(*this == tree);
}

/**
 * Retrieve method
 * Searches for NodeData in the tree and returns a pointer to it if found
 * @pre The binary search tree is properly initialized and sorted according to BST properties.
 * @post If the data is found, ptr points to the NodeData object in the tree that matches the data; otherwise, ptr is set to nullptr. 
 * tree is unchanged.
 */
bool BinTree::retrieve(const NodeData &data, NodeData *&ptr)
{
    Node *temp = retrieveHelper(this->root, data, ptr);
    return temp != nullptr;
}

/**
 * Retrieve helper method
 * Recursively searches for the given data in the tree and returns the node containing it
 * @pre The node parameter is either a valid node of the tree or nullptr (in case of reaching a leaf's child).
 * @post If data is found, ptr is set to point to the matching NodeData and returns the node containing it; if not found, ptr is set to nullptr. 
 * tree is unchanged.
 */
BinTree::Node *BinTree::retrieveHelper(Node *node, const NodeData &data, NodeData *&ptr)
{
    if (node == nullptr)
    {
        ptr = nullptr;
        return nullptr;
    }
    else if (*node->data == data)
    {
        ptr = node->data;
        return node;
    }
    else if (*node->data < data)
        return retrieveHelper(node->right, data, ptr);
    else
        return retrieveHelper(node->left, data, ptr);
}

/**
 * Get height method
 * Calculates the height of the node with the specified NodeData
 * @pre The binary search tree is properly initialized. The toFind data is assumed to potentially exist within the tree.
 * @post Tree is unchanged.
 * Returns the height of the node if found; otherwise, returns 0. 
 */
int BinTree::getHeight(const NodeData &toFind)
{
    int height = 0;
    heightHelper(root, toFind, height);
    return height;
}

/**
 * Height helper method
 * Recursive helper to calculate the height of a node
 * @pre none
 * @post Tree is unchanged.
 */
int BinTree::heightHelper(Node *&current, const NodeData &theNode, int &theHeight)
{
    if (!current)
    {
        return 0;
    }
    int lHeight = heightHelper(current->left, theNode, theHeight);
    int rHeight = heightHelper(current->right, theNode, theHeight);
    if (*current->data == theNode)
    {
        theHeight = (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
    }
    return (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
}

/**
 * Converts binary search tree to array
 * Performs an inorder traversal of the tree to store NodeData in an array and empties the tree
 * @pre Assumes the array is large enough to hold all NodeData pointers from the tree
 * @post The tree is empty and the array contains the NodeData from the tree in inorder
 */
void BinTree::bstreeToArray(NodeData *arr[])
{
    int i = 0;
    bstreeToArrayHelper(root, arr, i);
    destructorHelper(root);
}

/**
 * Helper for bstreeToArray
 * Recursively stores NodeData from the tree to an array in inorder sequence
 * @pre Node pointers and array are valid
 * @post All nodes are visited in inorder, NodeData pointers are stored in array, tree nodes are set to nullptr
 */
void BinTree::bstreeToArrayHelper(Node *node, NodeData *arr[], int &i)
{
    if (node)
    {
        bstreeToArrayHelper(node->left, arr, i);
        arr[i] = node->data;
        node->data = nullptr;
        i++;
        bstreeToArrayHelper(node->right, arr, i);
    }
}

/**
 * Converts array to binary search tree
 * Builds a balanced BST from a sorted array of NodeData* and empties the array
 * @pre The array is sorted and correctly sized
 * @post The tree is balanced with NodeData from the array, array entries set to nullptr
 */
void BinTree::arrayToBSTree(NodeData *arr[])
{
    destructorHelper(root);

    int size = 0;
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] != nullptr)
        {
            size++;
        }
        else
        {
            break;
        }
    }
    size--;

    arrayToBSTreeHelper(root, arr, 0, size);
}

/**
 * Helper for arrayToBSTree
 * Recursively builds a balanced BST from a sorted array segment
 * @pre start and end define the current segment of the array being used
 * @post subtree is built from array segment, nodes in the segment set to nullptr
 */
void BinTree::arrayToBSTreeHelper(Node *node, NodeData *arr[], int start, int end)
{
    if (start > end)
    {
        node = nullptr;
        return;
    }
    int midpoint = (start + end) / 2;
    NodeData *data = arr[midpoint];
    arr[midpoint] = nullptr;
    insert(data);
    arrayToBSTreeHelper(node, arr, start, (midpoint - 1));
    arrayToBSTreeHelper(node, arr, (midpoint + 1), end);
}

// given function
void BinTree::sideways(Node *current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }

        cout << *current->data << endl; // display information of object
        sideways(current->left, level);
    }
}

/**
 * Helper to display the tree sideways, starts recursive sideways display of the tree
 * @pre None
 * @post Tree is displayed sideways from root, tree structure is unchanged
 */
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

/**
 * Checks if the tree is empty, returns a boolean indicating if the tree has no nodes
 * @pre None
 * @post Tree is unchanged
 * Returns true if the tree is empty, false otherwise. 
 */
bool BinTree::isEmpty() const
{
    return root == nullptr;
}

/**
 * Empties the tree
 * Clears all nodes from the tree to free all memory
 * @pre A binary search tree exists
 * @post The tree is empty and all memory previously used by nodes is freed
 */
void BinTree::makeEmpty()
{
    destructorHelper(root);
}

/**
 * Inserts a new NodeData into the binary search tree
 * Creates a new node for the data and inserts it in the correct location to maintain BST properties
 * @pre The dataPtr points to a valid NodeData object
 * @post The tree contains the new data in the correct order, 
 * returns false if data already exists
 */
bool BinTree::insert(NodeData *dataPtr)
{
    Node *newPtr = new Node;
    newPtr->data = dataPtr;
    dataPtr = nullptr;
    newPtr->left = newPtr->right = nullptr;
    if (isEmpty())
    {
        root = newPtr;
    }
    else
    {
        Node *current = root;
        bool inserted = false;
        while (!inserted)
        {
            if (*newPtr->data == *current->data)
            {
                delete newPtr;
                newPtr = nullptr;
                return false;
            }
            else if (*newPtr->data < *current->data)
            {
                if (current->left == nullptr)
                {
                    current->left = newPtr;
                    inserted = true;
                }
                else
                {
                    current = current->left;
                }
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = newPtr;
                    inserted = true;
                }
                else
                {
                    current = current->right;
                }
            }
        }
    }
    return true;
}

/**
 * Printer function
 * Recursively performs inorder traversal to print the data in the tree
 * @pre None
 * @post Outputs the tree's data in inorder to the standard output, tree remains unchanged
 */
void BinTree::printer(const Node *node) const
{
    if (node != nullptr)
    {
        printer(node->left);
        cout << *node->data << " ";
        printer(node->right);
    }
}