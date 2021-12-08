#ifndef TREE_H_
#define TREE_H_

enum NODE_TYPES{
    CONST,
    SIGN,
    VAR
};

struct Node_t{
    NODE_TYPES type;
    double data;
    Node_t *left;
    Node_t *right;
};

struct BTree{
    Node_t *aNodes;
    int Size;
};

#endif