#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret;
        if (strs.size() == 0 || strs[0].size() == 0) return ret;
        for (size_t i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];
            for (size_t j = 1; j < strs.size(); ++j ) {
                if (strs[j].size() <= i || c != strs[j][i]) return ret;
            }
            ret.push_back(c);
        }
        return ret;
    }
};

int main()
{
    Solution s;
    vector<string> v{"flower","flow","flight"};
    cout << s.longestCommonPrefix(v) << endl;
}
