#ifndef DIFF_H_
#define DIFF_H_

#include <assert.h>
#include "tree/tree.h"
#include "onegin/oneggin.h"
#include "optimizator/optimizator.h"

#ifndef MAKE_CONST
#define MAKE_CONST(val) nodeCtor(CONST, val, NULL, NULL)
#endif

#ifndef MAKE_FUNC
#define MAKE_FUNC(val) nodeCtor(FUNC, val, copy_tree(LEFT), NULL)
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

#ifndef IS_E
#define IS_E ((node->left->type == VAR) && (strncmp(aVal[(int)node->left->data], "e", 1) == 0))
#endif

#ifndef START_LATEX
#define START_LATEX do {                                                \
                        fprintf(output, "\\documentclass{article}\n"    \
                        "\\usepackage{amsmath}\n"                       \
                        "\\usepackage[english, russian]{babel}"         \
                        "\\usepackage[utf8]{inputenc}\n"                \
                        "\\begin{document}\n\n"                         \
                        "Продифференцируем следующее выражение:\n");    \
                    } while (0)
#endif

#ifndef LATEX_RES
#define LATEX_RES   do {                                    \
                        fprintf(output, "Результат:\n");    \
                    } while (0)
#endif

#ifndef SIMPLIFY_LATEX
#define SIMPLIFY_LATEX  do {                                        \
                            fprintf(output, "Упростим ответ:\n");   \
                        } while (0)
#endif


#ifndef END_LATEX
#define END_LATEX   do {                                            \
                            fprintf(output, "$\n\n"                 \
                                            "\\end{document}");     \
                    } while (0)
#endif


Node_t* r_tree();

Node_t *diff_node(Node_t *node);
Node_t *copy_tree(Node_t *node);

#endif