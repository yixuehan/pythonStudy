#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    // bool isCapital(char c)
    // {
    //     return 'A' <= c && c <= 'Z';
    // }
    bool detectCapitalUse(string word) {
        if (word.size() <= 1) return true;
        bool flag ;
        if (!isupper(word[0])) {
            flag = false;
        }
        else {
            flag = isupper(word[1]);

        }
        for (size_t i = 1; i < word.size(); ++i) {
            cout << flag << ":" << (isupper(word[i]) != 0) << endl;
            cout <<  (flag != (isupper(word[i]) != 0)) << endl;
            if (flag != (isupper(word[i] != 0))) return false;
        }
        return true;
    }
};

int main()
{
    Solution s;
    cout << s.detectCapitalUse("mL") << endl;
}
