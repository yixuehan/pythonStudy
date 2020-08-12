#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    FILE *fp = fopen("data.dat", "rb");
    char buffer[100] = {};
    fread(buffer, 1, sizeof(buffer), fp);
    cout << buffer << endl;
}
