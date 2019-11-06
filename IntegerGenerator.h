#include "Generator.h"

#ifndef INTEGER_GENERATOR
#define INTEGER_GENERATOR

class IntegerGenerator : public Generator {
protected:
    LongInt MOD;
public:
    IntegerGenerator(LongInt mod);
    virtual LongInt randInt()=0;
};

#endif

