#include "diff.h"
#include "rec_cum/language.h"

char *str = {};
char aVal[N_VAL][MAX_NAME] = {}; 

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


Node_t *diff_node(Node_t *node) {
    assert(node);

    Node_t *res = NULL;

    switch(node->type) {

        case CONST: {
            res = MAKE_CONST(0);
            break;
        }

        case VAR: {
            res = MAKE_CONST(1);
            break;
        }

        case SIGN: {

            switch ((int)node->data) {

                case (int)'+': {
                    Node_t *new_left  = diff_node(node->left);
                    Node_t *new_right = diff_node(node->right);
                    res = RETURN_NODE('+');
                    break;
                }

                case (int)'-': {
                    Node_t *new_left  = diff_node(node->left);
                    Node_t *new_right = diff_node(node->right);
                    res = RETURN_NODE('-');
                    break;
                }

                case (int)'*': {
                    Node_t *new_left  = nodeCtor(SIGN, '*', diff_node(node->left), COPY_VAR(right));
                    Node_t *new_right = nodeCtor(SIGN, '*', COPY_VAR(left), diff_node(node->right));
                    res = RETURN_NODE('+');
                    break;
                }

                case (int)'/': {

                    Node_t *left_left  = nodeCtor(SIGN, '*', diff_node(node->left), COPY_VAR(right));
                    Node_t *left_right = nodeCtor(SIGN, '*', COPY_VAR(left), diff_node(node->right));
                    Node_t *new_left   = nodeCtor(SIGN, '-', left_left, left_right);
                    Node_t *new_right  = nodeCtor(SIGN, '^', COPY_VAR(right), MAKE_CONST(2));
                    res = RETURN_NODE('/');
                    break;
                } 

                case (int)'^': {

                    if (node->right->data - 1 == 1) {
                        res = COPY_VAR(left); 
                    }
                    else {
                        Node_t *new_left = COPY_VAR(right);
                        Node_t *right_right = nodeCtor(SIGN, '-', COPY_VAR(right), MAKE_CONST(1));
                        Node_t *new_right = nodeCtor(SIGN, '^', COPY_VAR(left), right_right);
                        res = RETURN_NODE('*'); 
                    }
                    
                    break;
                }

                default: {
                    printf("hernya kakaya-to\n");
                    abort();
                }

            }

            break;
        }

        case FUNC: {

            switch((int)node->data) {

                case SIN: {
                    res = MAKE_FUNC(COS);
                    break;
                }

                case COS: {
                    Node_t *new_left  = MAKE_CONST(0);
                    Node_t *new_right = MAKE_FUNC(SIN);
                    res = RETURN_NODE('-');
                    break;
                }

                case TG: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_FUNC(COS);
                    Node_t *right_right = MAKE_CONST(2);
                    Node_t *new_right   = MAKE_RIGHT('^');
                    res = RETURN_NODE('/');
                    break;
                }

                case CTG: {
                    Node_t *Left        = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_FUNC(SIN);
                    Node_t *right_right = MAKE_CONST(2);
                    Node_t *Right       = MAKE_RIGHT('^');
                    Node_t *new_right   = nodeCtor(SIGN, '/', Left, Right);
                    Node_t *new_left    = MAKE_CONST(0);
                    res = RETURN_NODE('-');
                    break;
                }

                case SQRT: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_CONST(2);
                    Node_t *right_right = MAKE_FUNC(SQRT);
                    Node_t *new_right   = MAKE_RIGHT('*');
                    res = RETURN_NODE('/');
                    break;
                }

                case LN: {
                    Node_t *new_left  = MAKE_CONST(1);
                    Node_t *new_right = COPY_VAR(left);
                    res = RETURN_NODE('/');
                    break;
                }

                case LOG: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = COPY_VAR(right);
                    Node_t *right_right = MAKE_FUNC(LN);
                    Node_t *new_right   = MAKE_RIGHT('*');
                    res = RETURN_NODE('/');
                    break;
                }

                default: {
                    printf("hernya kakaya-to\n");
                    abort();
                }

            }

        }

        //res = nodeCtor(SIGN, '*', n_res, diff_node(node->))

        break;
    }
    

    return res;
}


//-----------------------------------------------------------------------------


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
    //ASSERT(!node, "Void ptr");
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


//-----------------------------------------------------------------------------


int make_latex(Node_t *root, const char *file) {
    ASSERT(!root, "Void ptr");

    FILE *output = fopen(file, "w");
    ASSERT(!output, "Void ptr");

    fprintf(output,"$");
    record_node(root, output);
    fprintf(output,"$");

    fclose(output);

    return 0;
}


int record_node(Node_t *node, FILE* output) {
    ASSERT(!output, "Void ptr");

    if (!node)
        return 0;

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

            switch ((int)node->data) {
                
                case (int)'+': {
                    REC_ADD_SUB;
                }

                case (int)'-': {
                    REC_ADD_SUB;
                }

                case (int)'*': {
                    REC_MULT(node->left);
                    fprintf(output, "*");
                    REC_MULT(node->right);

                    break;
                }

                case (int)'/': {
                    fprintf(output, "\\frac{");
                    record_node(node->left, output);
                    fprintf(output, "}{");
                    record_node(node->right, output);
                    fprintf(output, "}");
                    break;
                }

                case (int)'^': {
                    if (IS_SIGN(node->left->data)) {
                    fprintf(output, "(");
                        record_node(node->left, output);
                        fprintf(output, ")"); 
                    }
                    else
                        record_node(node->left, output);

                    fprintf(output, "^{");
                    record_node(node->right, output);
                    fprintf(output, "}");
                    break;
                }

                default: {
                    printf("hernya kakaya-to\n");
                    abort();
                }

            }

            break;

        }
    
        case FUNC: {
            fprintf(output, "\\%s{", func[(int)node->data].name);
            record_node(node->left, output);
            fprintf(output, "}");

            if (node->data == LOG) {
                fprintf(output, "{");
                record_node(node->right, output);
                fprintf(output,"}");
            }

            break;
        }

        default: {
            printf("hernya kakaya-to\n");
            abort();
        }

    }

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