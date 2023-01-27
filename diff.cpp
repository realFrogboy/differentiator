#include "diff.h"
#include "rec_cum/language.h"

char *str = {};
extern char aVal[N_VAL][MAX_NAME]; 

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
                    // DIFFERENTIATE_SUM (LEFT, RIGHT, '+');
                    Node_t *new_left  = diff_node(LEFT);
                    Node_t *new_right = diff_node(RIGHT);
                    res = RETURN_NODE('+');
                    break;
                }

                case (int)'-': {
                    Node_t *new_left  = diff_node(LEFT);
                    Node_t *new_right = diff_node(RIGHT);
                    res = RETURN_NODE('-');
                    break;
                }

                case (int)'*': {
                    Node_t *new_left  = nodeCtor(SIGN, '*', diff_node(LEFT), copy_tree(RIGHT));
                    Node_t *new_right = nodeCtor(SIGN, '*', copy_tree(LEFT), diff_node(RIGHT));
                    res = RETURN_NODE('+');
                    break;
                }

                case (int)'/': {

                    Node_t *left_left  = nodeCtor(SIGN, '*', diff_node(LEFT), copy_tree(RIGHT));
                    Node_t *left_right = nodeCtor(SIGN, '*', copy_tree(LEFT), diff_node(RIGHT));
                    Node_t *new_left   = nodeCtor(SIGN, '-', left_left, left_right);
                    Node_t *new_right  = nodeCtor(SIGN, '^', copy_tree(RIGHT), MAKE_CONST(2));
                    res = RETURN_NODE('/');
                    break;
                } 

                case (int)'^': {

                    if ((LEFT->type == CONST) || IS_E) {
                        Node_t *new_left = copy_tree(node);
                        Node_t *new_right = MAKE_FUNC(LN); 

                        Node_t *ex_func = RETURN_NODE('*');
                        res = nodeCtor(SIGN, '*', ex_func, diff_node(RIGHT));
                    }

                    else {
                        Node_t *new_left = copy_tree(RIGHT);
                        Node_t *right_right = nodeCtor(SIGN, '-', copy_tree(RIGHT), MAKE_CONST(1));
                        Node_t *new_right = nodeCtor(SIGN, '^', copy_tree(LEFT), right_right);

                        Node_t *ex_func = RETURN_NODE('*'); 
                        res = nodeCtor(SIGN, '*', ex_func, diff_node(LEFT));
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

        case FUNC: { //diff_func ()

            Node_t *ex_func = NULL;

            switch((int)node->data) {

                case SIN: {
                    ex_func = MAKE_FUNC(COS);
                    break;
                }

                case COS: {         //diff_cos
                    Node_t *new_left  = MAKE_CONST(0);
                    Node_t *new_right = MAKE_FUNC(SIN);
                    ex_func = RETURN_NODE('-');
                    break;
                }

                case TG: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_FUNC(COS);
                    Node_t *right_right = MAKE_CONST(2);
                    Node_t *new_right   = MAKE_RIGHT('^');
                    ex_func = RETURN_NODE('/');
                    break;
                }

                case CTG: {
                    Node_t *Left        = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_FUNC(SIN);
                    Node_t *right_right = MAKE_CONST(2);
                    Node_t *Right       = MAKE_RIGHT('^');
                    Node_t *new_right   = nodeCtor(SIGN, '/', Left, Right);
                    Node_t *new_left    = MAKE_CONST(0);
                    ex_func = RETURN_NODE('-');
                    break;
                }

                case SQRT: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = MAKE_CONST(2);
                    Node_t *right_right = MAKE_FUNC(SQRT);
                    Node_t *new_right   = MAKE_RIGHT('*');
                    ex_func = RETURN_NODE('/');
                    break;
                }

                case LN: {

                    Node_t *new_left  = MAKE_CONST(1);
                    Node_t *new_right = copy_tree(LEFT);
                    ex_func = RETURN_NODE('/');
                    
                    break;
                }

                case LOG: {
                    Node_t *new_left    = MAKE_CONST(1);
                    Node_t *right_left  = copy_tree(LEFT);
                    Node_t *right_right = nodeCtor(FUNC, LN, copy_tree(RIGHT), NULL);
                    Node_t *new_right   = MAKE_RIGHT('*');
                    ex_func = RETURN_NODE('/');
                    break;
                }

                case ARCSIN: {
                    Node_t *new_left  = MAKE_CONST(1);
                    Node_t *sub_left  = MAKE_CONST(1);
                    Node_t *deg_left  = copy_tree(LEFT);
                    Node_t *deg_right = MAKE_CONST(2);
                    Node_t *deg       = nodeCtor(SIGN, '^', deg_left, deg_right);
                    Node_t *sub       = nodeCtor(SIGN, '-', sub_left, deg);
                    Node_t *new_right = nodeCtor(FUNC, SQRT, sub, NULL);
                    ex_func = RETURN_NODE('/');
                    break;
                }

                case ARCCOS: {
                    Node_t *new_left  = MAKE_CONST(0);
                    Node_t *Left      = MAKE_CONST(1);
                    Node_t *sub_left  = MAKE_CONST(1);
                    Node_t *deg_left  = copy_tree(LEFT);
                    Node_t *deg_right = MAKE_CONST(2);
                    Node_t *deg       = nodeCtor(SIGN, '^', deg_left, deg_right);
                    Node_t *sub       = nodeCtor(SIGN, '-', sub_left, deg);
                    Node_t *Right     = nodeCtor(FUNC, SQRT, sub, NULL);
                    Node_t *new_right = nodeCtor(SIGN, '/', Left, Right);
                    ex_func = RETURN_NODE('-');
                    break;
                }

                case ARCTG: {
                    Node_t *new_left  = MAKE_CONST(1);
                    Node_t *add_left  = MAKE_CONST(1);
                    Node_t *deg_left  = copy_tree(LEFT);
                    Node_t *deg_right = MAKE_CONST(2);
                    Node_t *deg       = nodeCtor(SIGN, '^', deg_left, deg_right);
                    Node_t *new_right = nodeCtor(SIGN, '+', add_left, deg);
                    ex_func = RETURN_NODE('/');
                    break;
                }

                case ARCCTG: {
                    Node_t *new_left  = MAKE_CONST(0);
                    Node_t *Left      = MAKE_CONST(1);
                    Node_t *add_left  = MAKE_CONST(1);
                    Node_t *deg_left  = copy_tree(LEFT);
                    Node_t *deg_right = MAKE_CONST(2);
                    Node_t *deg       = nodeCtor(SIGN, '^', deg_left, deg_right);
                    Node_t *Right     = nodeCtor(SIGN, '+', add_left, deg);
                    Node_t *new_right = nodeCtor(SIGN, '/', Left, Right);
                    ex_func = RETURN_NODE('-');
                    break;
                }


                default: {
                    printf("даня чемпион\n");
                    abort();
                }

            }
            // INTERNAL_FUNC
            res = nodeCtor(SIGN, '*', ex_func, diff_node(LEFT));
            // --------------
        }

        break;
    }
    
    return res;
}