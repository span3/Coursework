//What gets printed?

#include <iostream>
using namespace std;


class vec {
public:
    int * p;
    int len;

   void trunc(int amount) {  len -= amount; }
};

int main()
{
    vec v;
    static int A[] = { 1, 2, 3, 4, 5};
    v.len = 5;
    v.p = A;
    v.trunc(2);
    for (int i=0; i<v.len; i++)
        cout << v.p[i] << " ";
    cout << "\n";
}
