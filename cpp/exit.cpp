#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class A
{
public:
    ~A()
    {
        cout << "~A\n";
    }
};

A a2;

int main()
{
    A a;
    ofstream ofs("a.txt");
    std::exit(0);
}
