#include "diff.h"

char *str = {};

Node_t* r_tree() {
    FILE *input = fopen ("expression.txt", "rb");
    assert(input);

    str = read_f(input);
    char* old_str = str;

    Node_t *node = GetG();

    free(old_str);
    fclose(input);

    return node;
}


//-----------------------------------------------------------------------------


int make_graph(Node_t *root) {
    ASSERT(!root, "Void ptr");

    FILE *output = fopen("GRAPH_d.dot", "w");
    ASSERT(!output, "Can't open file");

    fprintf(output, "digraph tree {\n");;

    make_node(root, output);

    connect_node(root, output);

    fprintf(output, "}");

    fclose(output);

    return 0;
}

int make_node(Node_t *node, FILE *output) {
    ASSERT(!output, "Void ptr");

    if (!node) 
        return 0;

    static int num = 0;

    switch(node->type) {
        case CONST: {
            fprintf(output, "\tnode%d [shape = \"record\", style = \"filled\", fillcolor = \"greenyellow\", label = \"{<d>%lf|{NULL|NULL}}\"];\n", num, node->data);
            num++;
            break;
        }
        case SIGN: {
            fprintf(output, "\tnode%d [shape = \"record\", style = \"filled\", fillcolor = \"greenyellow\", label = \"{<d>%c|{<l>LEFT|<r>RIGHT}}\"];\n", num, (int)node->data);
            num++;
            break;
        }
        case VAR: {
            fprintf(output, "\tnode%d [shape = \"circle\", style = \"filled\", fillcolor = \"plightblue1\", label = \"{<d>%c|{NULL|NULL}}\"];\n", num, (int)node->data);
            num++;
            break;
        }
    }

    make_node(node->left, output);
    make_node(node->right, output);

    return 0;
}

int connect_node(Node_t *node, FILE *output) {
    ASSERT(!node, "Void ptr");
    ASSERT(!output, "Void ptr");

    if ((node->left == NULL) && (node->right == NULL))
        return 0;

    static int num = 0;
    int curr_num = num;

    num++;
    fprintf(output, "node%d:<l> -> node%d:<d>;\n", curr_num, num);

    connect_node(node->left, output);

    num++;
    fprintf(output, "node%d:<r> -> node%d:<d>;\n", curr_num, num);

    connect_node(node->right, output);

    return 0;
}


//-----------------------------------------------------------------------------


int delete_node(Node_t *node) {
    ASSERT(!node, "Void ptr");

    if ((node->left == NULL) && (node->right == NULL)) {
        free(node);
        return 0;
    }

    delete_node(node->left);
    delete_node(node->right);

    free(node);

    return 0;
}