// Main File

#include <iostream>
#include "BinaryTree.h"


int main() {
    BinaryTree* root = new BinaryTree(5);
    root->insert(7, root);
    root->insert(6, root);
    root->insert(8, root);
    root->insert(2, root);
    root->insert(1, root);
    root->insert(20, root);
    root->insert(41, root);
    root->insert(21, root);
    root->insert(-1, root);
    root->insert(3, root);
    root->insertInPlace(11, root);

    root->deleteNode(root, 11);

    root->printTree("", root, false);

    std::cout << root->findMaxDepth(root) << std::endl;
    std::cout << root->findMinDepth(root) << std::endl;

    root->inOrder(root);
    std::cout << std::endl;
    root->preOrder(root);
    std::cout << std::endl;
    root->postOrder(root);
}
