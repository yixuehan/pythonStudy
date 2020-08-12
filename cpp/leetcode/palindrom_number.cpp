#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = 0, t = x;
        while (x > 0) {
            y = (x%10) + 10 * y;
            x /= 10;
        }
        cout << y << ' ' << t << endl;
        return y == t;
    }
};

int main()
{
    Solution s;
    cout << s.isPalindrome(121) << endl;
}
