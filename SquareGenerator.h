#include "IntegerGenerator.h"

#ifndef SQUARE_GENERATOR
#define SQUARE_GENERATOR

class SquareGenerator : public IntegerGenerator {
protected:
    LongInt A, C, D, lastInt;
public:
    SquareGenerator(LongInt mod, LongInt a, LongInt c, LongInt d);
    virtual LongInt randInt();
};

#endif
