#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "../tree/tree.h"

enum FUNCTIONS {
    SIN,
    COS,
    TG,
    CTG,
    SQRT,
    LN,
    LOG,

    NUMBER,

    NON_EXISTENT = -1
};

struct Func {
    char name[10]; //TODO: magic number
    FUNCTIONS num;
};

static Func func[NUMBER] = {{"sin\0" , SIN },
                            {"cos\0" , COS },
                            {"tg\0"  , TG  },
                            {"ctg\0" , CTG },
                            {"sqrt\0", SQRT},
                            {"ln\0"  , LN  },
                            {"log\0" , LOG }};

const int MAX_NAME = 100;
const int N_VAL = 10; //TODO: put in diff.cpp

#ifndef ASSERT
#define ASSERT(statement, text) do {                                                                                    \
                                     if (statement) {                                                                   \
                                        printf (" %s:%d, IN FUNCTION %s:\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);  \
                                        printf (#text);                                                                 \
                                        return 1;                                                                       \
                                    }                                                                                   \
                                } while (0)
#endif


Node_t* GetG();
Node_t* GetE();
Node_t* GetT();
Node_t* GetD();
Node_t* GetP();
Node_t* GetN();
Node_t* GetV();
Node_t* GetF(int func_num);

FUNCTIONS isFunc(const char *name);

Node_t* nodeCtor(NODE_TYPES type, double val, Node_t *left, Node_t *right);

#endif