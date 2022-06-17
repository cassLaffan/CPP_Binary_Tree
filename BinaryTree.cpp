#include "BinaryTree.h"

BinaryTree::BinaryTree(int root) {
	value = root;
	leftChild = nullptr;
	rightChild = nullptr;
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

int BinaryTree::deleteNode(int node) {

	return node;
}