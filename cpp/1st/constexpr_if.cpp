#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class addable
{
    T val;
public:
    addable(T v) : val{v} {}
    template <typename U>
    T add(U x) const {
        if constexpr(is_same<vector<U>, T>::value) {
            auto copy(val);
            for ( auto &n : copy ) {
                n += x;
            }
            return copy;
        } else {
            return val + x;
        }
    }
};

int main()
{
    cout << addable<int>{1}.add(2) << endl;
    //strs = {"aa", "bb", "cc"};
    addable<vector<string>> str_add({"aa", "bb", "cc"});
    auto res = str_add.add("xyz"s);
    for (auto &r : res) {
        cout << r << endl;
    }
}
