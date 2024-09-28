#ifndef BTREE_H
#define BTREE_H

#include "table.h"

typedef struct BTreeNode {
    Table* table;
    struct BTreeNode** children;
    int num_children;
    int is_leaf;
} BTreeNode;

typedef struct {
    BTreeNode* root;
    int t;
} BTree;

BTree* create_btree(int t);
void insert_btree(BTree* tree, Table* table);

#endif
