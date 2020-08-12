#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.size() < 3) return result;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            int l = i+1, r = nums.size()-1;
            while (l < r) {
                int temp = nums[i] + nums[l] + nums[r];
                if ( 0 == temp ) {
                    result.push_back(vector<int>{nums[i], nums[l], nums[r]});
                    do {
                        ++l;
                    } while (l<r && (nums[l] == nums[l+1])) ;
                    do {
                        --r;
                    } while (l<r && (nums[r] == nums[r-1])) ;
                }
                else if (0 < temp) {
                    --r;
                }
                else {
                    ++l;
                }
            }
            while ((i+1) < nums.size() && nums[i] == nums[i+1]) ++i;
        }
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> v{-1,0,1,2,-1,-4};
    auto res = s.threeSum(v);
    for (auto &v : res) {
        cout << "[";
        for (auto value : v) {
            cout << value << ' ';
        }
        cout << "]" << endl;
    }
}
