#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    struct LessStr
    {
        bool operator()(const string &s1, const string &s2) const
        {
            return memcmp(s1.c_str(), s2.c_str(), 26) < 0;
        }
    };
    string convertNumList(const string &s)
    {
        string ret ;
        ret.resize(26);
        for (auto c : s) {
            ++ret[c-'a'];
        }
        return ret;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> retss;
        if (strs.size() == 0) {
            return retss;
        }
        map<string, int, LessStr> group_index;
        for (auto &str : strs) {
            auto str_conv = convertNumList(str);
            auto iter = group_index.find(str_conv);
            if ( iter != group_index.end()) {
                retss[iter->second].push_back(str);
            }
            else {
                group_index.emplace(str_conv, retss.size());
                retss.push_back(vector<string>{str});
            }
        }
        return retss;
    }
};

int main()
{
    vector<string> v{"eat","tea","tan","ate","nat","bat"};
    Solution s;
    auto retss = s.groupAnagrams(v);
    for (auto &rets : retss) {
        for (auto &ret : rets) {
            cout << ret << ' ';
        }
        cout << endl;
    }
}
