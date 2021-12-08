#include "diff.h"

int main() {
    Node_t *root = r_tree();

    make_graph(root);

    delete_node(root);

    return 0;
}