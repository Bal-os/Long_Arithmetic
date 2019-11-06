#include "SquareGenerator.h"

#ifndef LINEAR_GENERATOR
#define LINEAR_GENERATOR

class LinearGenerator : public SquareGenerator {
public:
    LinearGenerator(LongInt mod, LongInt a, LongInt c);
};

#endif
