#include "BinaryTree.h"

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

BinaryTree* BinaryTree::insert(int num, BinaryTree* tree) {
	if (tree == nullptr) {
		tree = new BinaryTree(num);
		return tree;
	}
	else {
		if (num < tree->getValue()) {
			if(tree->getLeft() != nullptr)
				insert(num, tree->getLeft());
			else {
				tree->leftChild = new BinaryTree(num);
				return tree;
			}
		}
		else {
			if (tree->getRight() != nullptr)
				insert(num, tree->getRight());
			else {
				tree->rightChild = new BinaryTree(num);
				return tree;
			}
		}	
	}
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

void BinaryTree::search(int num, BinaryTree* tree) {
	if (tree->getValue() == num) {
		tree->printTree("", tree, false);
	}
	else {
		if (num < tree->getValue()) {
			if (tree->getLeft() != nullptr)
				search(num, tree->getLeft());
		}
		else {
			if (tree->getRight() != nullptr)
				search(num, tree->getRight());
			else
				return;
		}
	}
}

void BinaryTree::invertTree(BinaryTree* tree) {
	if (tree == nullptr) {
		return;
	}
	else {
		BinaryTree* temp;
		temp = tree->getLeft();
		tree->leftChild = tree->getRight();
		tree->rightChild = temp;

		invertTree(tree->getLeft());
		invertTree(tree->getRight());
	}
}

int BinaryTree::deleteNode(BinaryTree* root, int node) {
	//Either the tree is empty or we've reached a leaf that does not contain this node
	if (root == nullptr || (root->getLeft() == nullptr && root->getRight() == nullptr && root->getValue() != node)) {
		return INT_MAX;
	}
	else if (root->getLeft() != nullptr && root->getLeft()->getValue() == node) {
		root->leftChild = nullptr;
		return node;
	}
	else if (root->getRight() != nullptr && root->getRight()->getValue() == node) {
		root->rightChild = nullptr;
		return node;
	}
	else if (node > root->getValue()) {
		return deleteNode(root->getLeft(), node);
	}
	else if (node < root->getValue()) {
		return deleteNode(root->getRight(), node);
	}
	// Two children, find the successor leaf
	else if (root->getLeft() != nullptr && root->getRight() != nullptr && root->getValue() == node) {
		BinaryTree* temp = root->getLeft();
		while (temp->getRight()->getRight() != nullptr) {
			temp = temp->getRight();
		}
		root->value = temp->getRight()->getValue();
		temp->rightChild = nullptr;
		return node;
	}
	// One child, moves everything up
	else if (root->getLeft() == nullptr && root->getRight() != nullptr && root->getValue() == node) {
		memcpy(root, root->getRight(), sizeof(root->getRight()));
	}
	else if (root->getLeft() != nullptr && root->getRight() == nullptr && root->getValue() == node) { 
		memcpy(root, root->getRight(), sizeof(root->getLeft()));
		
	}

	return node;
}