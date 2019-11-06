#include "SquareGenerator.h"

SquareGenerator::SquareGenerator(LongInt mod, LongInt a, LongInt c, LongInt d) : IntegerGenerator(mod), A(a), C(c), D(d), lastInt(c)
{
}

LongInt SquareGenerator::randInt()
{
    LongInt square = lastInt * lastInt % MOD;
    return lastInt = ( D * square + A * lastInt + C ) % MOD;
}
