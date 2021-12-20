#include "latexmaker.h"
#include "../func_info.h"

extern char aVal[N_VAL][MAX_NAME];

int make_latex(Node_t *root, FILE *output) {
    ASSERT(!root, "Void ptr");
    ASSERT(!output, "Void ptr");

    fprintf(output, "$$");
    record_node(root, output);
    fprintf(output, "$$\n\n");

    return 0;
}

int record_node(Node_t *node, FILE *output) {
    ASSERT(!output, "Void ptr");

    if (!node)
        return 0;
    
    if (PUT_BRACKET_LEFT) 
        fprintf(output, "(");
    
    if ((int)node->data == (int)'/')
        fprintf(output, "\\frac{");
    
    if (node->type == FUNC)
        fprintf(output, "\\%s{", func[(int)node->data].name);

    
    record_node(node->left, output);


    switch(node->type) {

        case CONST: {
            fprintf(output, "%.2lf", node->data);
            break;
        }

        case VAR: { 
            fprintf(output, "%s", aVal[(int)node->data]);
            break;
        }

        case SIGN: {
            
            if (PUT_BRACKET_LEFT) 
                fprintf(output, ")");
            
            if ((int)node->data == (int)'/')
                fprintf(output, "}{");
            
            else if ((int)node->data == (int)'^')
                fprintf(output, "^{");

            else if ((int)node->data == (int)'*')
                fprintf(output, "\\cdot ");

            else   
                fprintf(output, "%c", (int)node->data);
            
            break;
        }

        case FUNC: {
            fprintf(output, "}");

            if ((int)node->data == LOG) 
                fprintf(output, "{");
            
            break;
        }

        default: {
            break;
        }

    }

    if (PUT_BRACKET_RIGHT) 
        fprintf (output, "(");


    record_node(node->right, output);


    switch (node->type) {
        
        case SIGN: {
            
            if (PUT_BRACKET_RIGHT) 
                fprintf(output, ")");
            
            if (((int)node->data == (int)'/') || ((int)node->data == (int)'^'))
                fprintf(output, "}");
            
            break;
        }

        case FUNC: {
            if ((int)node->data == LOG) 
                fprintf(output, "}");
            
            break;
        }

        default: {
            break;
        }
    }

    return 0;
}