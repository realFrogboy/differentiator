#ifndef DIFF_H_
#define DIFF_H_

#include <assert.h>
#include "tree/tree.h"
#include "onegin/oneggin.h"

#ifndef MAKE_CONST
#define MAKE_CONST(val) nodeCtor(CONST, val, NULL, NULL)
#endif

#ifndef COPY_VAR
#define COPY_VAR(var) nodeCtor(node->var->type, node->var->data, node->var->left, node->var->right)
#endif

#ifndef MAKE_FUNC
#define MAKE_FUNC(val) nodeCtor(FUNC, val, COPY_VAR(left), NULL)
#endif

#ifndef RETURN_NODE
#define RETURN_NODE(val) nodeCtor(SIGN, val, new_left, new_right)
#endif

#ifndef MAKE_RIGHT
#define MAKE_RIGHT(val) nodeCtor(SIGN, val, right_left, right_right)
#endif

#ifndef IS_PLUS_MINUS
#define IS_PLUS_MINUS(val) (val == '+') || (val == '-')
#endif

#ifndef IS_SIGN
#define IS_SIGN(val) (val == '+') || (val == '-') || (val == '*') || (val == '/')
#endif

#ifndef REC_ADD_SUB
#define REC_ADD_SUB do {                                            \
                        record_node(node->left, output);            \
                        fprintf(output, "%c", (int)node->data);     \
                        record_node(node->right, output);           \
                        break;                                      \
                    } while (0)
#endif

#ifndef REC_MULT
#define REC_MULT(val)   do {                                    \
                            if (IS_PLUS_MINUS(val->data)) {     \
                                fprintf(output, "(");           \
                                record_node(val, output);       \
                                fprintf(output, ")");           \
                            }                                   \
                            else                                \
                                record_node(val, output);       \
                        } while (0)
#endif

Node_t* r_tree();

Node_t *diff_node(Node_t *node);

int make_graph(Node_t *root, const char *file);
int make_node(Node_t *node, FILE *output);
int connect_node(Node_t *node, FILE *output);

int make_latex(Node_t *root, const char *file);
int record_node(Node_t *node, FILE* output);

int delete_node(Node_t *node);

#endif