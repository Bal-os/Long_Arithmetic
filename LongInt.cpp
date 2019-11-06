#include "LongIntAlg.h"
#include "LongInt.h"
#include <cstdlib>

LongInt::LongInt(const std::string&input)
{
    LL st = 1;
    int ps = 0;
    int frst = 0;

    minus = false;
    if(input.size() > 0 && input[frst] == '-')minus = true, frst = 1;

    for(int i = (int)input.size() - 1; i >= frst; i--, st *= 10)
    {
        if(st >= BASE)ps++, st = 1;
        if(ps == val.size())val.push_back(0);
        val[val.size() - 1] += st * (input[i] - '0');
    }
}

LongInt::LongInt(LL input) : minus(false)
{
    if(input < 0)input = -input, minus = true;
    while(input > 0)
    {
        val.push_back(input % BASE);
        input /= BASE;
    }
    if(val.size() == 0)val.push_back(0);
}

LongInt::LongInt(std::vector<LL> input, bool minus): val(input), minus(minus)
{
    normalize(*this);
}

LongInt::LongInt() : LongInt("")
{
}

LongInt::~LongInt()
{
}

LongInt& LongInt::operator =(const LongInt &X)
{
    minus = X.minus;
    val = X.val;
    return *this;
}

LongInt::LongInt(const LongInt &X)
{
    minus = X.minus;
    val = X.val;
}
LongInt::LongInt(const LongInt &&X)
{
    minus = X.minus;
    val = X.val;
}

LongInt operator +(const LongInt &X,const LongInt &Y)
{
    int fac1 = 1, fac2 = 1;
    if(X.minus)fac1 *= -1;
    if(Y.minus)fac2 *= -1;

    LongInt R("");
    R.val.size();
    for(int i = 0; i < std::max(X.size(), Y.size()); ++i)
    {
        R.val.push_back((i < X.size() ? X.get(i) : 0) * fac1
                       +(i < Y.size() ? Y.get(i) : 0) * fac2);
    }
    normalize(R);
    return R;
}
LongInt operator -(const LongInt &X, const LongInt &Y)
{
    int fac1 = 1, fac2 = -1;
    if(X.minus)fac1 *= -1;
    if(Y.minus)fac2 *= -1;

    LongInt R("");
    R.val.size();
    for(int i = 0; i < std::max(X.size(), Y.size()); ++i)
    {
        R.val.push_back((i < X.size() ? X.get(i) : 0) * fac1
                       +(i < Y.size() ? Y.get(i) : 0) * fac2);
    }
    normalize(R);
    return R;
}
LongInt operator -(const LongInt &X)
{
    LongInt R = X;
    R.minus ^= 1;
    return R;
}
LongInt operator *(const LongInt &X, const LongInt &Y)
{
    LL fac = 1;
    if(X.minus)fac *= -1;
    if(Y.minus)fac *= -1;

    LongInt R = standart_mul(abs(X), abs(Y));
    if(fac < 0)R.minus ^= 1;
    return R;
}
LongInt operator /(const LongInt &X, const LongInt &Y)
{
    LL fac = 1;
    if(X.minus)fac *= -1;
    if(Y.minus)fac *= -1;

    LongInt R = standart_div(abs(X), abs(Y));
    if(fac < 0)R.minus ^= 1;
    return R;
}
LongInt operator /(const LongInt &X, LL y)
{
    return standart_div(X, LongInt(y) );
}

LongInt operator %(const LongInt& X, const LongInt& Y)
{
    LL fac = 1;
    if(X.minus)fac *= -1;
    if(Y.minus)fac *= -1;
    LongInt R = abs(X) - abs(X) / abs(Y) * abs(Y);
    if(fac < 0)R.minus ^= 1;
    return R;
}

LongInt& LongInt::operator +=(const LongInt&X)
{
    return *this = *this + X;
}
LongInt& LongInt::operator -=(const LongInt&X)
{
    return *this = *this - X;
}
LongInt& LongInt::operator *=(const LongInt&X)
{
    return *this = *this * X;
}
LongInt& LongInt::operator /=(const LongInt&X)
{
    return *this = *this / X;
}
LongInt& LongInt::operator %=(const LongInt&X)
{
    return *this = *this % X;
}

LongInt& LongInt::operator ++()
{
    *this += LongInt(1);
    return *this;
}
LongInt& LongInt::operator --()
{
    *this -= LongInt(1);
    return *this;
}

bool operator < (const LongInt& X, const LongInt &Y)
{
    if(X.minus && !Y.minus)return true;
    if(!X.minus && Y.minus)return false;

    if(X.size() < Y.size())return true;
    if(X.size() > Y.size())return false;
    for(int i = X.size() - 1; i >= 0; i--)
    {
        if(X.get(i) < Y.get(i))return true;
        if(X.get(i) > Y.get(i))return false;
    }
    return false;
}
bool operator == (const LongInt &X,const LongInt &Y)
{
    if(X.minus != Y.minus)return false;
    if(X.size() != Y.size())return false;
    for(int i = 0; i < X.size(); ++i)
        if(X.get(i) != Y.get(i))return false;
    return true;
}
bool operator != (const LongInt &X,const LongInt &Y)
{
    return !(X == Y);
}
bool operator > (const LongInt& X, const LongInt &Y)
{
    if(X < Y || X == Y)return false;
    return true;
}
bool operator <= (const LongInt& X, const LongInt &Y)
{
    return !(X > Y);
}

LL& LongInt::operator[](int n)
{
    return val[n];
}

int LongInt::size() const
{
    return val.size();
}

LL LongInt::get(int n) const
{
    return val[n];
}
//using namespace std;
void LongInt::shiftLeft(int len)
{
    int sz = val.size();
    for(int i = 0; i < len; ++i)val.push_back(0);
    for(int i = (int)val.size() - 1; i >= (int)val.size() - sz; --i)
    {
        //cout << i << ' ' << sz << ' ' << (int)val.size() - sz << "gg" << endl;
        val[i] = val[i - len];
        val[i - len] = 0;
    }
    normalize(*this);
    //cout << endl;
}

std::ostream& operator << (std::ostream &out, const LongInt &X)
{
    if(X.minus)out << "-";
    out << X.get(X.size() - 1);
    for(int i = X.size() - 2; i >= 0; i--){
        for(int j = 1; j < X.EXP; ++j)if(X.get(i) < X.POW[j])out << 0;
        out << X.get(i);
    }
    return out;
}
std::istream& operator >> (std::istream &in, LongInt &X)
{
    std::string input;
    in >> input;
    X = LongInt(input);
    return in;
}
