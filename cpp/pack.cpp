#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

#pragma pack(8)

struct test7
{
    char a;
    int b;
    char c;
};

struct test8
{
    char c;
    double a;
    char b;
};

struct test9
{
    char c;
    test7 a;
    test8 b;
    int x;
    char d;
};

struct test10
{
    double d;
    int c;
    int f;
    char b;
    int e;
};

struct s1{
// short a;
    double b;
// char b[8];
};
struct s2{
char c;
s1 d;
long long e;
};

int main()
{
    cout << sizeof(test7) << ' '
         << sizeof(test8) << ' '
         << sizeof(test9) << ' '
         << sizeof(test10) << ' '
         << sizeof(s2) << ' '
         << sizeof(s1) << ' '
         << endl;
    s2 s;
    cout << (void*)&s.c << ' '
         << (void*)&s.d << ' '
         << (void*)&s.e << ' '
         << endl;
    test10 t;
    cout << (void*)&t.d << ' '
         << (void*)&t.c << ' '
         << (void*)&t.f << ' '
         << (void*)&t.b << ' '
         << (void*)&t.e << ' '
         << endl;
}

