#ifndef BIG_INTEGER_ALG
#define BIG_INTEGER_ALG

#include "LongInt.h"
#include "Generators.h"

#include <complex>
typedef std::complex<double> cd;


void normalize_len(LongInt &);
void light_normalize(LongInt &);
void normalize(LongInt &);
void normalize_sign(LongInt &);

LongInt sqrt(LongInt A);
LongInt abs(LongInt A);
LongInt pow(LongInt A, LongInt N);
LongInt pow_mod(LongInt A, LongInt N, LongInt MOD);
LongInt fac(LongInt N);
LongInt gcd(LongInt A, LongInt B);

//MUL DIV
LongInt standart_mul(LongInt A, LongInt B);
LongInt standart_div(LongInt A, LongInt B);
LongInt karatsuba_mul(LongInt A, LongInt B);
LongInt toom_mul(LongInt A, LongInt B);
std::vector<cd> FFT(std::vector<cd> A);
LongInt FFT_mul(LongInt A, LongInt B);

//PRIME
bool prime(LongInt A);
bool primeFerma(LongInt A);
bool primeMillerRabin(LongInt A);
int jacobi(LongInt A, LongInt N);
bool primeSolovayStrassen(LongInt A);

#endif
