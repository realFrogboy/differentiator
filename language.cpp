#include "language.h"

extern char *str;

Node_t* GetG() {
    Node_t* res = GetE();

    if (*str != '\0')
        assert(0);
    
    return res;
}


Node_t* GetE() {
    Node_t *res = GetT();

    while ((*str == '+') || (*str == '-')) {
        char sign = *str;
        str++;
        
        Node_t *val = GetT();
        res = nodeCtor(SIGN, (int)sign, res, val); 
    }

    return res;
}


Node_t* GetT() {
    Node_t *res = GetP();

    while ((*str == '*') || (*str == '/')) {
        char sign = *str;
        str++;
        
        Node_t *val = GetP();
        res = nodeCtor(SIGN, (int)sign, res, val);
    }

    return res;
}


Node_t* GetP() {
    if (*str == '(') {
        str++;
        Node_t* res = GetE();

        if (*str == ')') {
            str++;
            return res;
        }
        else {
           assert(0);
        }
    }
    else {
        Node_t* res = GetN();
        return res;
    }
}


Node_t* GetN() {
    const char *old_str = str;
    int res = 0;

    while (('0' <= *str) && (*str <= '9')) {
        res = res * 10 + (*str - '0');
        str++;
    }

    if (old_str == str) 
        assert(0);

    return nodeCtor(CONST, res, NULL, NULL);
}

Node_t* GetV() {
    char res = '\0';

    if ((('a' <= *str) && (*str <= 'z')) || (('A' <= *str) && (*str <= 'Z')) || (*str == '_')) {
        res = *str;
        str++;
    }
    else 
        assert(0);

    return nodeCtor(VAR, res, NULL, NULL);
}


Node_t* nodeCtor(NODE_TYPES type, double val, Node_t *left, Node_t *right) {
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));
    assert(node); 

    node->type = type;
    node->data = val;
    node->left = left;
    node->right = right;

    printf("!!!\n");

    return node;
}