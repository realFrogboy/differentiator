#ifndef OPTIMIZATOR_H_
#define OPTIMIZATOR_H_

#include <stdio.h>
#include <string.h>
#include "../tree/tree.h"

#ifndef IS_LEFT
#define IS_LEFT(val)  ((node->left->type == CONST)  && (node->left->data == val))
#endif

#ifndef IS_RIGHT
#define IS_RIGHT(val) ((node->right->type == CONST) && (node->right->data == val))
#endif

#ifndef IS_LEFT_AND_RIGHT_CONSTS
#define IS_LEFT_AND_RIGHT_CONSTS (node->left->type == CONST) && (node->right->type == CONST)
#endif

#ifndef IS_LNE
#define IS_LNE (node->type == FUNC) && (node->data == LN) && (node->left->type == VAR) && (strncmp(aVal[(int)node->left->data], "e", 1) == 0)
#endif

Node_t *optimizate_tree(Node_t *node);
Node_t *delete_son(Node_t *node, Node_t *son);
Node_t *calc_node(Node_t *node);
Node_t *div_deg(Node_t *node, char sign);

#endif