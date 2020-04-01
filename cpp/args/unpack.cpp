#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

template <typename T, typename ...Args>
bool unpack(const vector<T> &l, Args &...args)
{
    if (l.size() != sizeof...(args)) {
        cout << "count error:" << l.size() << ' ' << sizeof...(args) << endl;
        return false;
    }
    int i = 0;
    initializer_list<int> {([](const vector<T> &l, int &i, auto &arg){
            arg = l[i];
            ++i;
            }(l, i, args), 0)...
    };
    cout << "success\n";
    return true;
}

template <typename T, typename ...Args>
bool unpack(vector<T> &&l, Args &...args)
{
    return unpack(l, args...);
}

int main()
{
    vector<string> l{"test1", "test2", "s1", "s2"};
    string s1, s2, s3, s4;
    unpack(vector<string> {"test1", "test2", "s1", "s2"}, s1, s2);
    unpack(vector<string> {"test1", "test2", "s1", "s2"}, s1, s2, s3, s4);
    cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << endl;

    unpack(l, s1, s2);
    unpack(l, s1, s2, s3, s4);
}
