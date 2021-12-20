#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include <assert.h>

enum NODE_TYPES{
    CONST,
    SIGN,
    VAR, 
    FUNC
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

#ifndef LEFT
#define LEFT node->left
#endif

#ifndef RIGHT
#define RIGHT node->right
#endif

int delete_node(Node_t *node);
Node_t *copy_tree(Node_t *node);
Node_t* nodeCtor(NODE_TYPES type, double val, Node_t *left, Node_t *right);

#endif