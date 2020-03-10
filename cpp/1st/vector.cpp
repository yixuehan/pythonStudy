#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v{1,2,3,4,5,6,7,8,9,2,34,6,6,2};
    //auto new_end = remove(begin(v), end(v), 2);
    //cout << *new_end << endl;
    //v.erase(new_end, end(v));
    v.erase(remove(begin(v), end(v), 2), end(v));

    for (auto i : v) {
        cout << i << ' ';
    }
    cout << endl;
    cout << *(end(v)-1) << endl;
}
