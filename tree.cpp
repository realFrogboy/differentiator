#include "tree.h"

Node_t* nodeCtor(NODE_TYPES type, double val, Node_t *left, Node_t *right) {
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));
    assert(node); 

    node->type = type;
    node->data = val;
    node->left = left;
    node->right = right;

    return node;
}

int delete_node(Node_t *node) {
    if (!node)
        return 0;

    delete_node(node->left);
    delete_node(node->right);

    free(node);

    return 0;
}


Node_t *copy_tree(Node_t *node) {
    if (node == NULL)
        return NULL;

    Node_t *new_left  = copy_tree(node->left);
    Node_t *new_right = copy_tree(node->right);

    return nodeCtor(node->type, node->data, new_left, new_right);
}