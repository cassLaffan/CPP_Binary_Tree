﻿#include "BinaryTree.h"

BinaryTree::BinaryTree(int root) {
	value = root;
	leftChild = nullptr;
	rightChild = nullptr;
}
// delet dis
BinaryTree::~BinaryTree() {
	delete(this->leftChild);
	delete(this->rightChild);
}

BinaryTree& BinaryTree::operator=(const BinaryTree & other) {
	this->leftChild = other.getLeft();
	this->rightChild = other.getRight();
	this->value = other.getValue();

	return *this;
}

BinaryTree* BinaryTree::insertInPlace(int num, BinaryTree* tree) {
	// Will only insert if the value is strictly greater than or less than. No repeats!
	if (num < tree->getValue()) {
		BinaryTree* newNode = new BinaryTree(num);

		if (tree->getLeft() == nullptr) {
			tree->leftChild = newNode;
		}
		else if (tree->getLeft()->getValue() < num) {
			newNode->leftChild = tree->getLeft();
			tree->leftChild = newNode;
		}
		else if (tree->getLeft()->getValue() > num) {
			newNode->rightChild = tree->getLeft();
			tree->leftChild = newNode;
		}
	}
	else if (num > tree->getValue())  {
		BinaryTree* newNode = new BinaryTree(num);

		if (tree->getRight() == nullptr) {
			tree->leftChild = newNode;
		}

		if (tree->getRight()->getValue() < num) {
			newNode->leftChild = tree->getRight();
			tree->rightChild = newNode;
		}
		else if (tree->getRight()->getValue() > num) {
			newNode->rightChild = tree->getRight();
			tree->rightChild = newNode;
		}
	}

	return tree;
}

BinaryTree* BinaryTree::insert(int num, BinaryTree* tree) {
	// Creates a new node here and now
	if (tree == nullptr) {
		tree = new BinaryTree(num);
	}
	// Inserts where necessary
	else {
		if (num < tree->getValue()) {
			if(tree->getLeft() != nullptr)
				insert(num, tree->getLeft());
			else {
				tree->leftChild = new BinaryTree(num);
			}
		}
		else {
			if (tree->getRight() != nullptr)
				insert(num, tree->getRight());
			else {
				tree->rightChild = new BinaryTree(num);
			}
		}	
	}
	return tree;
}

int BinaryTree::getValue() const {
	return this->value;
}

BinaryTree* BinaryTree::getRight() const {
	return this->rightChild;
}

BinaryTree* BinaryTree::getLeft() const {
	return this->leftChild;
}


int BinaryTree::findMinDepth(BinaryTree* root) const {
	if (root == nullptr) {
		return 0;
	}

	else if (root->getLeft() == nullptr && root->getRight() == nullptr) {
		return 1;
	}

	int left = INT_MAX;
	int right = INT_MAX;

	if (root->getLeft() != nullptr) {
		left = findMinDepth(root->getLeft());
	}

	if (root->getRight() != nullptr) {
		right = findMinDepth(root->getRight());
	}

	return std::min(left, right) + 1;

}

int BinaryTree::findMaxDepth(BinaryTree* root) const {
	if (root == nullptr) {
		return 0;
	}
	else {
		int left = findMaxDepth(root->getLeft());
		int right = findMaxDepth(root->getRight());

		if (left > right) {
			return left + 1;
		}
		else {
			return right + 1;
		}
	
	}
}

void BinaryTree::printTree(const std::string& prefix, BinaryTree* tree, bool isLeft) const{
	if (tree != nullptr){
		std::cout << prefix;

		std::cout << (isLeft ? "|__" : "|---");

		// print the value of the node
		std::cout << tree->value << std::endl;

		// enter the next tree level - left and right branch
		printTree(prefix + (isLeft ? "|   " : "    "), tree->getLeft(), true);
		printTree(prefix + (isLeft ? "|   " : "    "), tree->getRight(), false);
	}
}

// Will print the tree from where it finds the number
// Otherwise nothing happens
void BinaryTree::search(int num, BinaryTree* tree) {
	if (tree->getValue() == num) {
		tree->printTree("", tree, false);
	}
	else {
		if (num < tree->getValue()) {
			if (tree->getLeft() != nullptr){
				search(num, tree->getLeft());
			}
		}
		else {
			if (tree->getRight() != nullptr){
				search(num, tree->getRight());
			}
		}
	}
}

// Deleted the else
// Inverts the tree, duh
void BinaryTree::invertTree(BinaryTree* tree) {
	if (tree != nullptr) {
		BinaryTree* temp;
		temp = tree->getLeft();
		tree->leftChild = tree->getRight();
		tree->rightChild = temp;

		invertTree(tree->getLeft());
		invertTree(tree->getRight());
	}
}


// Functipons that check if a tree has children

bool BinaryTree::hasChildren(BinaryTree* tree) {
	return (tree->getRight() != nullptr) && (tree->getLeft() != nullptr);
}

bool BinaryTree::hasRightChild(BinaryTree* tree) {
	return (tree->getRight() != nullptr) && (tree->getLeft() == nullptr);
}

bool BinaryTree::hasLeftChild(BinaryTree* tree) {
	return (tree->getRight() == nullptr) && (tree->getLeft() != nullptr);
}


// Finds the littlist leaf (sarcasm)
int BinaryTree::getMinLeaf(BinaryTree* tree) {
	int minValue = tree->getLeft()->getValue();

	BinaryTree* temp = tree->getLeft();

	while (temp->getRight() != nullptr) {
		minValue = temp->getRight()->getValue();
		temp = temp->getRight();
	}

	return minValue;
}

// In cases where deletion is unsuccessful, the return value will be infinity
BinaryTree* BinaryTree::deleteNode(BinaryTree* root, int node) {
	//Either the tree is empty or we've reached a leaf that does not contain this node
	if (root == nullptr || !hasLeftChild(root) && !hasRightChild(root) && (!hasChildren(root) && root->getValue() != node)) {
		return root;
	}

	// The left node is the one we're looking for.
	if (root->getLeft() != nullptr && root->getLeft()->getValue() == node) {
		// No children
		if (!hasChildren(root->getLeft()) && !hasLeftChild(root->getLeft()) && !hasRightChild(root->getLeft())) {
			root->leftChild = nullptr;
		}

		// Two Children (three money?)
		else if (hasChildren(root->getLeft())) {
			int replacementValue = getMinLeaf(root->getLeft());
			root->getLeft()->value = replacementValue;
			deleteNode(root->getLeft(), replacementValue);
		}

		// One Child
		else if(hasRightChild(root->getLeft())) {
			root->leftChild = root->getLeft()->getRight();
		}
		else if (hasLeftChild(root->getLeft())) {
			root->leftChild = root->getLeft()->getLeft();
		}

	}

	// The right node is the one we're looking for.
	if (root->getRight() != nullptr && root->getRight()->getValue() == node) {

		// No children
		if (!hasChildren(root->getRight()) && !hasLeftChild(root->getRight()) && !hasRightChild(root->getRight())) {
			root->rightChild = nullptr;
		}

		// Two Children (three money?)
		else if (hasChildren(root->getRight())) {
			int replacementValue = getMinLeaf(root->getRight());
			root->getRight()->value = replacementValue;
			deleteNode(root->getRight(), replacementValue);
		}

		// One Child
		else if (hasRightChild(root->getRight())) {
			root->rightChild = root->getRight()->getRight();
		}
		else if (hasLeftChild(root->getRight())) {
			root->rightChild = root->getRight()->getLeft();
		}
	}
	
	// None of the immediate children are the correct child.
	if ((node < root->getValue() && root->getLeft() != nullptr) || root->getRight() == nullptr) {
		deleteNode(root->getLeft(), node);
	}
	else if ((node > root->getValue() && root->getRight() != nullptr) || root->getLeft() == nullptr) {
		deleteNode(root->getRight(), node);
	}

	return root;
}

// Printing Functions

void BinaryTree::inOrder(BinaryTree* tree) const {
	if (tree != nullptr) {
		inOrder(tree->getLeft());
		std::cout << " " << tree->getValue() << " ";
		inOrder(tree->getRight());
	}
}

void BinaryTree::preOrder(BinaryTree* tree) const {
	if (tree != nullptr) {
		std::cout << " " << tree->getValue() << " ";
		preOrder(tree->getLeft());
		preOrder(tree->getRight());	
	}
}

void BinaryTree::postOrder(BinaryTree* tree) const {
	if (tree != nullptr) {
		postOrder(tree->getLeft());
		postOrder(tree->getRight());
		std::cout << " " << tree->getValue() << " ";
	}
}