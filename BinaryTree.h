#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdio.h>
#include <string>
#include <iostream>

// Also acts as a node
// What is a node? A miserable pile of binary search trees.
class BinaryTree{
	int value;
	BinaryTree* leftChild;
	BinaryTree* rightChild;

public:
	BinaryTree(int);
	int getValue() const;
	BinaryTree* getRight() const;
	BinaryTree* getLeft() const;
	BinaryTree* insert(int, BinaryTree*);
	void search(int, BinaryTree*);
	int deleteNode(int);
	void printTree(const std::string&, BinaryTree*, bool) const;
};


#endif

