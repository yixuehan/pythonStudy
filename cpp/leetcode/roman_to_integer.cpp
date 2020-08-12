#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        std::unordered_map<char, int> m{
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
        };
        int res = 0;
        int pre = 0;
        int curr;
        for (int i = int(s.size())-1; i >= 0; --i) {
            curr = m[s[i]];
            if (curr < pre) res -= curr;
            else res += curr;
            pre = curr;
        }
        return res;
    }
};

int main()
{
    Solution s;
    cout << s.romanToInt("III") << endl;
    cout << s.romanToInt("IV") << endl;
    cout << s.romanToInt("IX") << endl;
    cout << s.romanToInt("LVIII") << endl;
    cout << s.romanToInt("MCMXCIV") << endl;
}
