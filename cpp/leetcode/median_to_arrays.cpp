#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        size_t l1 = 0,
               l2 = 0,
               findl = 0;
        const size_t posl = (nums1.size() + nums2.size() - 1) / 2,
                     posr = (nums1.size() + nums2.size()) / 2;
        int ml = nums1.size() ? nums1[0] : nums2[0];
        int mr = ml;
        if (0 == nums1.size()) {
            return (nums2[posl] + nums2[posr])/2.0;
        }
        else if (0 == nums2.size()){
            return (nums1[posl] + nums1[posr])/2.0;
        }
        while ( findl <= posl ) {
            if ( l1 < nums1.size() && nums1[l1] < nums2[l2] ) {
                ml = nums1[l1];
                ++l1;
            }
            else if ( l2 < nums2.size() ) {
                ml = nums2[l2];
                ++l2;
            }
            else {
                l1 = l1 + posl-findl;
                ml = nums1[l1];
                ++l1;
                findl = posl+1;
                break;
            }
            ++findl;
        }
        if ( findl == posr ) {
            if ( l1 >= nums1.size() ) {
                mr = nums2[l2];
            }
            else if ( l2 >= nums2.size() ) {
                mr = nums1[l1];
            }
            else if ( nums1[l1] < nums2[l2] ) {
                mr = nums1[l1];
            }
            else {
                mr = nums2[l2];
            }
        }
        else {
            mr = ml;
        }
        return (ml + mr) / 2.0;
        
    }
};

int main()
{
    //vector<int> v1{1,2,3,4,20,34,56,100};
    vector<int> v1{2,3,4,5,6};
    //vector<int> v2{34,45,65,77,88,1000};:
    vector<int> v2{1};
    Solution s;
    vector<int> v3;
    v3.insert(v3.end(), v1.begin(), v1.end());
    v3.insert(v3.end(), v2.begin(), v2.end());
    std::sort(v3.begin(), v3.end());
    for( auto v : v3 ) {
        cout << v << ' ';
    }
    cout << "\n";
    cout << s.findMedianSortedArrays(v1, v2) << "\n";
}
