#include "graphmaker.h"
#include "../func_info.h"

extern char aVal[N_VAL][MAX_NAME]; 

int make_graph(Node_t *root, const char *file) {
    ASSERT(!root, "Void ptr");

    FILE *output = fopen(file, "w");
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
    int curr_num = num;

    switch(node->type) {
        case CONST: {
            fprintf(output, "\tnode%d [shape = \"record\", style = \"filled\", fillcolor = \"greenyellow\", label = \"%.2lf\"];\n", num, node->data);
            num++;
            break;
        }
        case SIGN: {
            fprintf(output, "\tnode%d [shape = \"invtriangle\", style = \"filled\", fillcolor = \"pink\", label = \"%c\"];\n", num, (int)node->data);
            num++;
            break;
        }
        case VAR: {
            fprintf(output, "\tnode%d [shape = \"circle\", style = \"filled\", fillcolor = \"lightskyblue1\", label = \"%s\"];\n", num, aVal[(int)node->data]);
            num++;
            break;
        }

        case FUNC: {
            fprintf(output, "\tnode%d [shape = \"diamond\", style = \"filled\", fillcolor = \"gold\", label = \"%s\"];\n", num, func[(int)node->data].name);
            num++;
            break;
        }
    }

    make_node(node->left, output);
    make_node(node->right, output);

    if (!curr_num)
        num = 0;

    return 0;
}

int connect_node(Node_t *node, FILE *output) {
    ASSERT(!output, "Void ptr");

    if ((node->left == NULL) && (node->right == NULL))
        return 0;

    static int num = 0;
    int curr_num = num;

    num++;
    fprintf(output, "node%d -> node%d;\n", curr_num, num);

    connect_node(node->left, output);

    if (node->right != NULL) {
        num++;
        fprintf(output, "node%d -> node%d;\n", curr_num, num);

        connect_node(node->right, output);
    }

    if (!curr_num) 
        num = 0;
    
    return 0;
}