#include "optimizator.h"
#include "pow.h"
#include "../func_info.h"

extern char aVal[N_VAL][MAX_NAME]; 

Node_t *optimizate_tree(Node_t *node) {
    if(!node)
        return NULL;

    node->left  = optimizate_tree(node->left);
    node->right = optimizate_tree(node->right);

    if (node->type == SIGN) {

        switch ((int)node->data) {
            //common.c, common.h
            case '+': {

                if (IS_LEFT(0)) {
                    node = delete_son(node, node->right);
                }     

                else if (IS_RIGHT(0)) {
                    node = delete_son(node, node->left);
                }

                else if (IS_LEFT_AND_RIGHT_CONSTS) {
                    node = calc_node(node);
                }

                break;
            }

            case '-': {

                if (IS_LEFT(0)) {
                    Node_t *right_son = copy_tree(node->right);
                    delete_node(node);
                    node = nodeCtor(SIGN, '-', nodeCtor(SIGN, ' ', NULL, NULL), right_son); // ' ' for unary minus
                } 

                else if (IS_RIGHT(0)) {
                    node = delete_son(node, node->left);
                }

                else if (IS_LEFT_AND_RIGHT_CONSTS) {
                    node = calc_node(node);
                }

                break;
            }

            case '*': {

                if (IS_LEFT(0) || IS_RIGHT(0)) {
                    delete_node(node);
                    node = nodeCtor(CONST, 0, NULL, NULL);
                }

                else if (IS_RIGHT(1)) {
                    node = delete_son(node, node->left);
                }

                else if (IS_LEFT(1)) {
                    node = delete_son(node, node->right);
                }

                else if (IS_LEFT_AND_RIGHT_CONSTS) {
                    node = calc_node(node);
                }

                break;
            }

            case '/': {

                if (IS_LEFT(0) || IS_RIGHT(0)) {
                    printf("OPTIMIZATION ERROR: Division by ZERO!\n");
                }

                else if (IS_LEFT_AND_RIGHT_CONSTS) {
                    node = calc_node(node);
                }

                break;
            }

            case '^': {

                if (IS_RIGHT(1)) {
                    node = delete_son(node, node->left);
                }

                else if (IS_LEFT_AND_RIGHT_CONSTS && (node->right->data - (int)node->right->data == 0)) {
                    node = calc_node(node);
                }

                else if ((node->right->type == SIGN) && (node->right->data == '+')) {
                    node = div_deg(node, '*');
                }

                else if ((node->right->type == SIGN) && (node->right->data == '-')) {
                    node = div_deg(node, '/');
                }

                break;
            }

            default: {
                break;
            }

        }
    }

    else if (IS_LNE) {
        delete_node(node);
        node = nodeCtor(CONST, 1, NULL, NULL);
    }

    return node;
}

Node_t *delete_son(Node_t *node, Node_t *son) {
    assert(node);
    assert(son);

    Node_t *tmp = copy_tree(son);
    delete_node(node);
    node = copy_tree(tmp);
    delete_node(tmp);

    return node;
}

Node_t *calc_node(Node_t *node) {
    assert(node);

    double val = 0;
    
    switch ((int)node->data) {

        case '+': {
            val = node->left->data + node->right->data;
            break;
        }

        case '-': {
            val = node->left->data - node->right->data;
            break;
        }

        case '*': {
            val = node->left->data * node->right->data;
            break;
        }

        case '/': {
            val = node->left->data / node->right->data;
            break;
        }

        case '^': {
            val = pow_mod((unsigned long long)node->left->data, (unsigned long long)node->right->data);
            break;
        }

    }

    delete_node(node);
    node = nodeCtor(CONST, val, NULL, NULL);

    return node;
}

Node_t *div_deg(Node_t *node, char sign) {
    assert(node);

    Node_t *left_left   = copy_tree(node->left);
    Node_t *left_right  = copy_tree(node->right->left);
    Node_t *new_left    = nodeCtor(SIGN, '^', left_left, left_right);
    Node_t *right_left  = copy_tree(node->left);
    Node_t *right_right = copy_tree(node->right->right);
    Node_t *new_right   = nodeCtor(SIGN, '^', right_left, right_right);
    Node_t *new_node    = nodeCtor(SIGN, sign, new_left, new_right);

    delete_node(node);
    node = copy_tree(new_node);
    delete_node(new_node);

    return node;
}