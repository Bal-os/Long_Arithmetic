#ifndef BIG_INTEGER
#define BIG_INTEGER
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef long long LL;

class LongInt
{
private:
    const int POW[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    const int EXP = 1;
public:
    const int BASE = POW[EXP];
    LongInt& operator =(const LongInt &);
    LongInt(const std::string&);
    LongInt(LL);
    LongInt(std::vector<LL>, bool);
    LongInt(const LongInt&);
    LongInt(const LongInt&&);
    LongInt();
    ~LongInt();
    std::vector<LL> val;
    bool minus;
    int size() const;
    LL get(int n)const;
    LL& operator[](int n);
    friend bool operator == (const LongInt&, const LongInt&);
    friend bool operator != (const LongInt&, const LongInt&);
    friend bool operator < (const LongInt&, const LongInt&);
    friend bool operator > (const LongInt&, const LongInt&);
    friend bool operator <= (const LongInt&, const LongInt&);
    friend LongInt operator +(const LongInt&, const LongInt&);
    friend LongInt operator -(const LongInt&, const LongInt&);
    friend LongInt operator -(const LongInt&);
    friend LongInt operator *(const LongInt&, const LongInt&);
    friend LongInt operator /(const LongInt&, const LongInt&);
    friend LongInt operator /(const LongInt&, LL);
    friend LongInt operator %(const LongInt&, const LongInt&);
    LongInt& operator +=(const LongInt&);
    LongInt& operator -=(const LongInt&);
    LongInt& operator *=(const LongInt&);
    LongInt& operator /=(const LongInt&);
    LongInt& operator %=(const LongInt&);
    LongInt& operator ++();
    LongInt& operator --();
    void shiftLeft(int);
    friend std::ostream& operator << (std::ostream&,const LongInt&);
    friend std::istream& operator >> (std::istream&,LongInt&);
};

#include "LongIntAlg.h"

#endif // BIG_INTEGER
