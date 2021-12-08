#ifndef DIFF_H_
#define DIFF_H_

#include <assert.h>
#include "tree/tree.h"
#include "rec_cum/language.h"
#include "onegin/oneggin.h"

Node_t* r_tree();

int make_graph(Node_t *root);
int make_node(Node_t *node, FILE *output);
int connect_node(Node_t *node, FILE *output);

int delete_node(Node_t *node);

#endif