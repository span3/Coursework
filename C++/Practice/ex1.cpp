//What gets printed? 

#include <iostream>
using namespace std;

class T {
public:
    T() {}
};

class S {
public:
    static int i;
    S()    { i++; }
    S(int unused) { i += 2; }
    S(T unused)   { i += 3; }
};

int S::i = 0;

S f(S unused)
{
    return 0;
}

S g(S& unused)
{
    return 1;
}

int main()
{
    cout << S::i << "\n";
    S s1, s2(2);
    cout << S::i << "\n";
    T t;
    cout << S::i << "\n";
    S s3(t);
    cout << S::i << "\n";
    f(t);
    cout << S::i << "\n";
    g(s1);
    cout << S::i << "\n";
}
