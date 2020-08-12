#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
// #include <cstdint>
#include <climits>
using namespace std;
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        auto iter_end = std::unique(nums.begin(), nums.end());
        if (iter_end - nums.begin() >= 3) {
            cout << "存在:" << INT_MIN << endl;
            for (auto iter = nums.begin(); iter < iter_end; ++iter) {
                cout << *iter << ' ';
            }
            cout << endl;
            return *(iter_end-3);
        }
        cout << "不存在" << endl;
        return *(iter_end-1);
    }
};

int main() {
    Solution s;
    vector<int> v{3, 2, INT_MIN};
    
    s.thirdMax(v);
}
