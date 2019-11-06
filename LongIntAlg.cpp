#include "LongIntAlg.h"

void normalize_len(LongInt &X)
{
    while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
}

void light_normalize(LongInt &X)
{
    X.val.push_back(0);
    for(int i = 0; i < X.size(); ++i)
    {
        if(X[i] < 0)X[i + 1]--, X[i] += X.BASE;
        if(X[i] >= X.BASE)X[i + 1]++, X[i] -= X.BASE;
    }
    while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
    normalize_sign(X);
}

void normalize(LongInt &X)
{
    X.val.push_back(0);
    for(int i = 0; i + 1 < X.size(); ++i)
    {
        int carr = X[i] / X.BASE;
        X[i] %= X.BASE;
        if(X[i] < 0)X[i] += X.BASE, carr--;
        X[i + 1] += carr;
    }
    normalize_len(X);
    normalize_sign(X);
}

void normalize_sign(LongInt &X)
{
    if(X[X.size() - 1] < 0)
    {
        X.minus ^= 1;
        for(int i = 0; i < X.size(); ++i)X[i] = -X[i];
        for(int i = 0; i + 1 < X.size(); ++i)
        {
            if(X[i] < 0)X[i] += X.BASE, X[i + 1]--;
        }
        while(X.size() > 1 && X[X.size() - 1] == 0)X.val.pop_back();
    }
}

LongInt sqrt(LongInt A)
{
    LongInt l = 0;
    LongInt r = A;
    while(l < r)
    {
        LongInt mid = (l + r + 1) / 2;
        if(mid * mid <= A) l = mid;
        else r = mid - 1;
    }
    return l;
}

LongInt pow(LongInt A, LongInt N)
{
    LongInt R("1");
    while(N > 0)
    {
        if(N % 2 == 1)R *= A;
        A *= A;
        N /= 2;
    }
    return R;
}
LongInt pow_mod(LongInt A, LongInt N, LongInt MOD)
{
    LongInt R("1");
    while(N > 0)
    {
        if(N % 2 == 1)R *= A, R %= MOD;
        A *= A;
        A %= MOD;
        N /= 2;
    }
    return R;
}
LongInt abs(LongInt A)
{
    A.minus = false;
    return A;
}

LongInt fac(LongInt N)
{
    LongInt R(1);
    for(LongInt i = 1; i <= N; ++i)
    {
        R *= i;
    }
    return R;
}

LongInt gcd(LongInt A, LongInt B)
{
    if(A == 0)return B;
    return gcd(B % A, A);
}

//MUL DIV

LongInt standart_mul(LongInt X, LongInt Y)
{
    LongInt R("");
    int sign = 1;
    if(X < 0)sign = -sign;
    if(Y < 0)sign = -sign;
    X = abs(X);
    Y = abs(Y);

    for(int i = 0; i < X.size() + Y.size(); ++i)R.val.push_back(0);
    for(int i = 0; i < X.size(); ++i)
    {
        for(int j = 0; j < Y.size(); ++j)
        {
            R[i + j] += X.get(i) *
                        Y.get(j);
            if(R[i + j] >= R.BASE)
            {
                R[i + j + 1] += R[i + j] / R.BASE;
                R[i + j] %= R.BASE;
            }
        }
    }
    if(sign < 0)R = -R;
    normalize(R);
    return R;
}

LongInt standart_div(LongInt X, LongInt Y)
{
    LongInt R("");
    int sign = 1;
    if(X < 0)sign = -sign;
    if(Y < 0)sign = -sign;
    X = abs(X);
    Y = abs(Y);
    LongInt A("0");
    LongInt B = Y;
    B.minus = false;

    LongInt BASE(R.BASE);

    for(int i = X.size() - 1; i >= 0; i--)
    {
        A *= BASE;
        A += X.get(i);

        LL l = 0;
        LL r = R.BASE - 1;
        while(l < r)
        {
            LL mid = (l + r + 1) / 2;
            if(B * LongInt(mid) <= A)l = mid;
            else r = mid - 1;
        }
        A -= B * LongInt(l);
        R.val.push_back(l);
    }
    reverse(R.val.begin(), R.val.end());
    while(R.size() > 1 && R[R.size() - 1] == 0)R.val.pop_back();

    if(sign < 0)R = -R;
    normalize(R);
    return R;
}

const LL MIN_KARATSUBA_LEN = 3;

#include <iostream>
using namespace std;
void karatsuba_divide(LongInt &A, LongInt &A0, LongInt &A1, int len)
{
    for(int i = 0; i < len; ++i)A0.val.push_back(i < A.size() ? A[i] : 0);
    for(int i = len; i < len + len; ++i)A1.val.push_back(i < A.size() ? A[i] : 0);
    normalize_len(A0);
    normalize_len(A1);
}

LongInt karatsuba_mul(LongInt A, LongInt B)
{
    int len = std::max(A.size(), B.size());
    if(len < MIN_KARATSUBA_LEN)return standart_mul(A, B);
    len = (len + 1) / 2;
    LongInt R("");
    LongInt A0, A1, B0, B1;
    karatsuba_divide(A, A0, A1, len);
    karatsuba_divide(B, B0, B1, len);

    LongInt M0 = karatsuba_mul(A0 , B0);
    LongInt M2 = karatsuba_mul(A1 , B1);

    LongInt M1 = karatsuba_mul((A0 + A1), (B0 + B1)) - M0 - M2;


    int SZ1 = M1.size(), SZ2 = M2.size();

    for(int i = 0; i < len; ++i)M1.val.push_back(0), M2.val.push_back(0), M2.val.push_back(0);
    for(int i = M1.size() - 1; i >= M1.size() - SZ1; --i)
    {
        M1[i] = M1[i - len];
        M1[i - len] = 0;
    }
    for(int i = M2.size() - 1; i >= M2.size() - SZ2; --i)
    {
        M2[i] = M2[i - len - len];
        M2[i - len - len] = 0;
    }

    return M0 + M1 + M2;
}

const int TOOM_SIZE = 3;

void toom_divide(LongInt A, LongInt &A0, LongInt &A1, LongInt &A2, int size)
{
    for(int i = 0; i < A.size(); ++i)
    {
        if(i < size)A0.val.push_back(A[i]);
        else if(i < size + size)A1.val.push_back(A[i]);
        else A2.val.push_back(A[i]);
    }
    normalize(A0);
    normalize(A1);
    normalize(A2);
}
LongInt toom_mul(LongInt A, LongInt B)
{
    if(A.size() + B.size() < TOOM_SIZE)
        return standart_mul(A, B);

    int sign = 1;
    if(A < 0)sign = -sign;
    if(B < 0)sign = -sign;
    A = abs(A);
    B = abs(B);
    int sz = std::max(A.size(), B.size());
    int i = ceil(A.size() / 3.);
    while(A.size() < i)A.val.push_back(0);
    while(B.size() < i)B.val.push_back(0);



    LongInt m0;
	LongInt m1;
	LongInt m2;

	LongInt n0;
	LongInt n1;
	LongInt n2;
    toom_divide(A, m0, m1, m2, i);
    toom_divide(B, n0, n1, n2, i);
	LongInt p0 = m0;
	LongInt p1 = m0 + m1 + m2;
	LongInt abc = m0 - m1;
	LongInt abs = abc + m2;
	LongInt pMinus1 = abs;
	LongInt pMinus2 = m0 - m1*2 + m2*4;
	LongInt pInf = m2;

	LongInt q0 = n0;
	LongInt q1 = n0 + n1 + n2;
	LongInt qMinus1 = n0 - n1 + n2;
	LongInt qMinus2 = n0 - n1*2 + n2*4;
	LongInt qInf = n2;

	LongInt r0 = toom_mul(p0, q0);
	LongInt r1 = toom_mul(p1, q1);
	LongInt rMinus1 = toom_mul(pMinus1, qMinus1);
	LongInt rMinus2 = toom_mul(pMinus2, qMinus2);
	LongInt rInf = toom_mul(pInf, qInf);

	LongInt r_0 = r0;
	LongInt r_4 = rInf;
	LongInt r_3 = (rMinus2 - r1) / 3;
	LongInt r_1 = (r1 - rMinus1) / 2;
	LongInt r_2 = rMinus1 - r0;
	r_3 = (r_2 - r_3) / 2;
	rInf = rInf* 2;
	r_3 = r_3 + rInf;
	r_2 = r_2 + r_1 - r_4;
	r_1 = r_1 - r_3;
    r_1.shiftLeft(i * 1);
    r_2.shiftLeft(i * 2);
    r_3.shiftLeft(i * 3);
    r_4.shiftLeft(i * 4);

    LongInt R = r_0 + r_1 + r_2 + r_3 + r_4;
    if(sign < 0) R = -R;
    normalize(R);
    return R;
}

std::vector<cd> FFT(std::vector<cd> A)
{
    int n = A.size();
    if(n == 1)return A;
    std::vector<cd> A0, A1;
    for(int i = 0; i < n; ++i)
    {
        if(i & 1)A1.push_back(A[i]);
        else A0.push_back(A[i]);
    }

    A0 = FFT(A0);
    A1 = FFT(A1);

    double ang = 2 * acos(-1) / n;
    for(int i = 0; i < n / 2; ++i)
    {
        cd wi = cd(cos(ang * i), sin(ang * i));
        A[i] = A0[i] + wi * A1[i];
        A[i + n / 2] = A0[i] - wi * A1[i];
    }
    return A;
}


LongInt FFT_mul(LongInt A, LongInt B)
{
    int sz = A.size() + B.size();
    int N = 1;
    while(N < sz)N <<= 1;
    std::vector<cd> A1(N), B1(N);
    for(int i = 0; i < N; ++i)
    {
        A1[i] = i < A.size() ? A[i] : 0;
        B1[i] = i < B.size() ? B[i] : 0;
    }

    std::vector<cd> FFT1 = FFT(A1);
    std::vector<cd> FFT2 = FFT(B1);

    for(int i = 0; i < N; ++i)FFT1[i] *= FFT2[i];

    FFT1 = FFT(FFT1);

    for(int i = 0; i < N; ++i)FFT1[i] /= N;
    reverse(FFT1.begin() + 1, FFT1.end());

    std::vector<LL> r(N);
    for(int i = 0; i < N; ++i)r[i] = LL(0.5 + FFT1[i].real());

    LongInt R(r, false);

    return R;
}

//PRIME

bool prime(LongInt A){
    if(A == 2)return true;
    if(A % 2 == 0)return false;
    LongInt sq = sqrt(A);
    for(LongInt i = 3; i <= sq; i += 2){
        if(A % i == 0)return false;
    }
    return true;
}

const LongInt RAND_A("2819128"), RAND_C("13251828"), RAND_D("2183192171");
const int FERMA_ITER = 30;

bool primeFerma(LongInt A)
{
    if(A == 1)return false;
    if(A == 2 || A == 3)return true;
    LongInt rnd;
    SquareGenerator gen(A - 1, RAND_A, RAND_C, RAND_D);
    for(int i = 0; i < FERMA_ITER; ++i)
    {
        rnd = gen.randInt() + 1;
        if(pow_mod(rnd, A - 1, A) != 1)return false;
    }
    return true;
}

const int MILLER_RABIN_ITER = 60;

bool primeMillerRabin(LongInt A)
{
    if(A == 2)return true;
    if(A % 2 == 0)return false;

    LongInt rnd;
    SquareGenerator gen(A - 1, RAND_A, RAND_C, RAND_D);

    LongInt A1 = A - 1;
    LongInt Q = A1;
    int p = 0;
    LongInt R;
    while(Q % 2 == 0)
    {
        p++;
        Q /= 2;
    }

    for(int i = 0; i < MILLER_RABIN_ITER; ++i)
    {
        rnd = gen.randInt() + 1;
        R = pow_mod(rnd, Q, A);
        if(R == 1 || R == A1)return true;

        for(int j = 1; j < p; ++j)
        {
            R = R * R % A;
            if(R == A1)return true;
        }
    }
    return false;
}

const int SOLOVAY_STRASSEN_ITER = 30;

int jacobi(LongInt A, LongInt N)
{
    int r = 1;
    while(A != 0)
    {
        while(A % 2 == 0)
        {
            A /= 2;
            LongInt k = N % 8;
            if(k == 3 || k == 5)r = -r;
        }
        std::swap(N, A);
        if(A % 4 == N % 4 && N % 4 == 3)r = -r;
        A %= N;
    }
    if(N == 1)return r;
    else return 0;
}

bool primeSolovayStrassen(LongInt A)
{
    if(A == 2)return true;
    if(A % 2 == 0)return false;

    LongInt rnd;
    LongInt A1 = A - 1;
    LongInt Ahalf = A1 / 2;
    SquareGenerator gen(A1, RAND_A, RAND_C, RAND_D);

    for(int i = 0; i < SOLOVAY_STRASSEN_ITER; ++i)
    {
        rnd = gen.randInt();
        int jac = jacobi(rnd, A);
        LongInt pw = pow_mod(rnd, Ahalf, A);
        if(jac == 0 && pw != 0)return false;
        if(jac == 1 && pw != 1)return false;
        if(jac == -1 && pw != A1)return false;
    }
    return true;
}
