#include <iostream>
#include <algorithm>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    string addStrings(string num1, string num2) {
        if (num1.size() < num2.size())
            return addStrings(std::move(num2), std::move(num1));
        
        bool flag = false;
        string result;
        result.reserve(num1.size()+1);
        int pos2 = num2.size();
        --pos2;
        int pos1 = num1.size();
        --pos1;
        cout << pos1 << ":" << pos2 << endl;
        for (; pos2 >= 0; --pos2, --pos1) {
            char value = num1[pos1]-'0' + num2[pos2] + flag;
            flag = (value > '9');
            value = value - 10 * flag;
            result.push_back(value);
        }
        while (pos1 >= 0) {
            if (flag) {
                char value = num1[pos1] + flag;
                flag = (value > '9');
                value = value - 10 * flag;
                result.push_back(value);
            }
            else {
                result.push_back(num1[pos1]);
            }
            --pos1;
        }
        if (flag) {
            result.push_back('1');
            result.insert(0, "1");
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

int main()
{
    Solution s;
    cout << s.addStrings("123456789", "1") << endl;
}
