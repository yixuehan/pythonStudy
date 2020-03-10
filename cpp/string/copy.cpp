#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;



int main()
{
    string s1;
    s1.resize(100);
    cout << s1.size() << endl;
    s1[10] = 'a';
    string s2(s1);
    cout << s2 << endl;
    cout << s2.size() << endl;
    cout << s2[10] << endl;
}
