#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        std::unordered_map<char, char> bracket{
            {'{', '}'},
            {'(', ')'},
            {'[', ']'},
        };
        size_t pos = 0, end = s.size();
        string left;
        // left.resize(s.size()+1);
        left.reserve(s.size()+1);
        if (end % 2) return false;
        if (end == 0) return true;

        while ( pos < end ) {
            if (left.size() == 0 || s[pos] != bracket[left.back()]) {
                left.push_back(s[pos]);
            }
            else {
                left.pop_back();
            }
            ++pos;
        }
        cout << "size:" << left.size() << ":" << left.length()  << ":" << left << endl;
        return left.size() == 0;
    }
};

int main()
{
    Solution s;
    cout << s.isValid("{}[]()") << endl;
    cout << s.isValid("{}]()") << endl;
    cout << s.isValid("{}[])") << endl;
    cout << s.isValid("{}[({})]()") << endl;
}
