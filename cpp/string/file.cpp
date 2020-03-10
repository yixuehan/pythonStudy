#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    fstream fs("a.txt", ios::out);
    string s = "abcdef123456";
    s[6] = '\0';
    fs << s;
}
