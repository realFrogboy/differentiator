#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "../tree/tree.h"
#include "../func_info.h"


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

#endif