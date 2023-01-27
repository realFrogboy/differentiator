#ifndef LATEXMAKER_H_
#define LATEXMAKER_H_

#include "../tree/tree.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef PUT_BRACKET_LEFT
#define PUT_BRACKET_LEFT (node->type == SIGN) && (((int)node->data == (int)'*') || (int)node->data == (int)'^') && (((int)node->left->data == (int)'+') || ((int)node->left->data == (int)'-'))
#endif

#ifndef PUT_BRACKET_RIGHT
#define PUT_BRACKET_RIGHT (node->type == SIGN) && ((int)node->data == (int)'*') && (((int)node->right->data == (int)'+') || ((int)node->right->data == (int)'-'))
#endif

#ifndef ASSERT
#define ASSERT(statement, text) do {                                                                                    \
                                     if (statement) {                                                                   \
                                        printf (" %s:%d, IN FUNCTION %s:\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
                                        printf (#text);                                                                 \
                                        return 1;                                                                       \
                                    }                                                                                   \
                                } while (0)
#endif

int make_latex(Node_t *root, FILE *output);
int record_node(Node_t *node, FILE *output);

#endif