#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // int a, b;
#if 0
    string a = "100", b = "200";
    int c = 300;
    string d = "xoapdad";
    ofstream ofs("out.txt");
    ofs << a << '\n' << b << '\n' << c << '\n' << d << '\n';
#else
    string a, b;
    int c;
    string d;
    ifstream ifs("out.txt");
    ifs >> a >> b >> c >> d;
    cout << a << ':' << b << ":" << c << ":" << d << endl;
#endif
}
