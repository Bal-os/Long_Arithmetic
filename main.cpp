#include "LongInt.h"
#include <iostream>

using namespace std;

int main()
{
    LongInt a, b;
    cin >> a >> b;
    cout << "multiplication:" << endl;
    cout << a * b << endl;
    cout << FFT_mul(a,b) << endl;
    cout << karatsuba_mul(a,b) << endl;
    cout << toom_mul(a,b) << endl;
    cout << "prime test:" << endl;
    cout << primeFerma(a) << endl;
    cout << primeSolovayStrassen (a) << endl;
    cout << primeMillerRabin(a) << endl;
    //cout << prime(a) << endl;
}
