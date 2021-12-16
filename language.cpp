#include "language.h"

extern char *str;
extern char aVal[N_VAL][MAX_NAME]; 

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
    Node_t *res = GetD();

    while ((*str == '*') || (*str == '/')) {
        char sign = *str;
        str++;
        
        Node_t *val = GetD();
        res = nodeCtor(SIGN, (int)sign, res, val);
    }

    return res;
}

Node_t* GetD() {
    Node_t *res = GetP();

    if (*str == '^') {
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
        Node_t *res = {};
        if (isalpha(*str))
            res = GetV();
        else
            res = GetN();

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
    char *str_old  = str;

    static int val_num = 0;

    int num = 0;
    char name[MAX_NAME] = {};
    while ((('a' <= *str) && (*str <= 'z')) || (('A' <= *str) && (*str <= 'Z'))) {
        name[num++] = *str;
        str++;
    }
    name[num] = '\0';
    
    if (str == str_old) 
        assert(0);

    int func_num = 0;
    if ((func_num = isFunc(name)) != NON_EXISTENT) 
        return GetF(func_num);

    else {
        strncpy(aVal[val_num], name, strlen(name) + 1);
        val_num++;
        return nodeCtor(VAR, val_num - 1, NULL, NULL);
    }
}

Node_t* GetF(int func_num) {
    Node_t *val1 = GetP();
    Node_t *val2 = NULL;

    if (func_num == LOG) 
        val2 = GetP();
    
    return nodeCtor(FUNC, func_num, val1, val2);
}


FUNCTIONS isFunc(const char *name) {
    assert(name);

    for (int num = 0; num < NUMBER; num++) {
        if (!strncmp(name, func[num].name, strlen(name))) 
            return func[num].num;
    }

    return NON_EXISTENT;
}


Node_t* nodeCtor(NODE_TYPES type, double val, Node_t *left, Node_t *right) {
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));
    assert(node); 

    node->type = type;
    node->data = val;
    node->left = left;
    node->right = right;

    return node;
}