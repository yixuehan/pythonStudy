#include <iostream>
#include <set>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

int main()
{
    multiset<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(1);
    cout << s.count(1) << endl;
    cout << s.erase(1) << endl;
    for (auto i : s) {
        cout << i << ' ';
    }
    cout << endl;
}
