// Main File

#include <iostream>
#include "BinaryTree.h"


int main() {
    BinaryTree* root = new BinaryTree(5);
    root->insert(6, root);
    root->insert(8, root);
    root->insert(2, root);
    root->insert(1, root);
    root->insert(20, root);
    root->insert(41, root);
    root->insert(21, root);
    root->insert(-1, root);
    root->insert(3, root);

    root->search(41, root);
}
