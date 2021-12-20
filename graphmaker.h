#ifndef GRAPHMAKER_H_
#define GRAPHMAKER_H_

#include "../tree/tree.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef ASSERT
#define ASSERT(statement, text) do {                                                                                    \
                                     if (statement) {                                                                   \
                                        printf (" %s:%d, IN FUNCTION %s:\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
                                        printf (#text);                                                                 \
                                        return 1;                                                                       \
                                    }                                                                                   \
                                } while (0)
#endif

int make_graph(Node_t *root, const char *file);
int make_node(Node_t *node, FILE *output);
int connect_node(Node_t *node, FILE *output);

#endif