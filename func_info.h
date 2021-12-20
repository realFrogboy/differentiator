#ifndef FUNC_INFO_H_
#define FUNC_INFO_H_

enum FUNCTIONS {
    SIN,
    COS,
    TG,
    CTG,
    SQRT,
    LN,
    LOG,
    ARCSIN,
    ARCCOS,
    ARCTG,
    ARCCTG,

    NUMBER,

    NON_EXISTENT = -1
};

struct Func {
    char name[10]; //TODO: magic number
    FUNCTIONS num;
};

static Func func[NUMBER] = {{"sin\0"   , SIN   },
                            {"cos\0"   , COS   },
                            {"tg\0"    , TG    },
                            {"ctg\0"   , CTG   },
                            {"sqrt\0"  , SQRT  },
                            {"ln\0"    , LN    },
                            {"log\0"   , LOG   },
                            {"arcsin\0", ARCSIN},
                            {"arccos\0", ARCCOS},
                            {"arctg\0" , ARCTG },
                            {"arcctg\0", ARCCTG}};

const int MAX_NAME = 20;
const int N_VAL = 10;

#endif