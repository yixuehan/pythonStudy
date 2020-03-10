#include <iostream>
#include <vector>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

constexpr size_t N = 1000000;

int searchInsert(vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] >= target) return i;
    }
    return nums.size();
}

int bsearchInsert(vector<int>& nums, int target) {
    int low = 0, high = nums.size()-1;

    // Invariant: the desired index is between [low, high+1]
    while (low <= high) {
        int mid = low + (high-low)/2;

        if (nums[mid] < target)
            low = mid+1;
        else
            high = mid-1;
    }

    // (1) At this point, low > high. That is, low >= high+1
    // (2) From the invariant, we know that the index is between [low, high+1], so low <= high+1. Follwing from (1), now we know low == high+1.
    // (3) Following from (2), the index is between [low, high+1] = [low, low], which means that low is the desired index
    //     Therefore, we return low as the answer. You can also return high+1 as the result, since low == high+1
    return low;
}

int main()
{
    vector<int> nums;
    for (size_t i = 0; i < N; ++i) {
        nums.push_back(i+1);
    }

    int find = 111;

    {
        int x = 0;
        timer::cpu_timer t;
        int index = bsearchInsert(nums, find);
        auto use_time = t.elapsed();
        cout << timer::format(use_time) << endl;
        cout << "binary index:" << index << endl;
        cout << "X:" << x << endl;
    }
    {
        int x = 0;
        timer::cpu_timer t;
        int index = searchInsert(nums, find);
        auto use_time = t.elapsed();
        cout << timer::format(use_time) << endl;
        cout << "index:" << index << endl;
        cout << "X:" << x << endl;
    }
}
