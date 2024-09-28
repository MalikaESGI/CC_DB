#include "btree.h"
#include <stdlib.h>

BTree* create_btree(int t) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = NULL;
    tree->t = t;
    return tree;
}

void insert_btree(BTree* tree, Table* table) {
    if (tree->root == NULL) {
        BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
        node->table = table;
        node->children = NULL;
        node->is_leaf = 1;
        tree->root = node;
    }
}
