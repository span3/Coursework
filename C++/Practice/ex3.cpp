//What does this program print?



#include <iostream>
using namespace std;

#define foo1( a )  a * a

int j = 6;

inline	int
foo2( int a ) {
    return a * a;
}

void
goo1( int& x )
{
    x = 3;
}

void
goo2( int  x )
{
    x = 3;
}

int main()
{
    int i, j = 12;

    cout << "foo1 = " << foo1( 3 + 2 ) << "\n";
    cout << "foo2 = " << foo2( 3 + 2 ) << "\n";

    i = 5;
    goo1( i );
    cout << "goo1 = " << i << "\n";
    i = 5;
    goo2( i );
    cout << "goo2 = " << i << "\n";

    cout << "  j = " <<   j << "\n";
    cout << "::j = " << ::j << "\n";
}
