#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <limits.h>

// Also acts as a node
// What is a node? A miserable pile of binary search trees.
class BinaryTree{
	int value;
	BinaryTree* leftChild;
	BinaryTree* rightChild;

public:
	BinaryTree(int);
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree&);

	int getValue() const;
	BinaryTree* getRight() const;
	BinaryTree* getLeft() const;
	BinaryTree* insertInPlace(int, BinaryTree*);
	BinaryTree* insert(int, BinaryTree*);
	bool hasChildren(BinaryTree*);
	bool hasRightChild(BinaryTree*);
	bool hasLeftChild(BinaryTree*);
	void search(int, BinaryTree*);
	BinaryTree* deleteNode(BinaryTree*, int);
	int getMinLeaf(BinaryTree*);
	void invertTree(BinaryTree*);
	void printTree(const std::string&, BinaryTree*, bool) const;
};


#endif

