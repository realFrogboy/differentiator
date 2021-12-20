#include "diff.h"
#include "rec_cum/language.h"
#include "latexmaker_for_diff/latexmaker.h"
#include "optimizator/optimizator.h"
#include "graphmaker_for_diff/graphmaker.h"
#include "func_info.h"

char aVal[N_VAL][MAX_NAME] = {}; 


int main() {
    Node_t *root = r_tree();

    root = optimizate_tree(root);
    root = optimizate_tree(root);

    make_graph(root, "GRAPH_d.dot");
    system("dot -Tpng GRAPH_d.dot -o image1.png");


    FILE *output = fopen("LATEX2.txt", "w");
    ASSERT(!output, "Void ptr");
    START_LATEX;

    make_latex(root, output);

    Node_t *root_d = diff_node(root);

    LATEX_RES;

    make_latex(root_d, output);

    make_graph(root_d, "GRAPH_dd.dot");
    system("dot -Tpng GRAPH_dd.dot -o image2.png");

    root_d = optimizate_tree(root_d);

    make_graph(root_d, "GRAPH_dd_op.dot");
    system("dot -Tpng GRAPH_dd_op.dot -o image3.png");

    SIMPLIFY_LATEX;

    make_latex(root_d, output);
    
    END_LATEX;

    fclose(output);

    delete_node(root);
    delete_node(root_d);

    return 0;
}