#include "diff.h"
#include "rec_cum/language.h"

int main() {
    Node_t *root = r_tree();

    make_graph(root, "GRAPH_d.dot");
    system("dot -Tpng GRAPH_d.dot -o image1.png");
    make_latex(root, "LATEX1.txt");

    Node_t *root_d = diff_node(root);

    make_graph(root_d, "GRAPH_dd.dot");
    system("dot -Tpng GRAPH_dd.dot -o image2.png");
    make_latex(root_d, "LATEX2.txt");

    delete_node(root);
    //delete_node(root_d);

    return 0;
}