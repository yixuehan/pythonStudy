#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    
    int climbStairs(int n) {
        // shared_ptr<size_t> way(new size_t[n], [](size_t *p){
        //     delete []p;
        // });
        // memset(way)
        
        size_t way[n+1] = {0, 1, 2};                       
        return climbStairs_r(n, way);
    }

    int climbStairs2(int n) {
        if (n < 3) return n;
        int step1 = 1, step2 = 2;
        int ret = 0;
        for (int i = 3; i <= n; ++i) {
            ret = step1 + step2;
            step1 = step2;
            step2 = ret;
        }
        return ret;
    }
    
    int climbStairs_r(int n, size_t way[]) {
        // cout << n << ":" << way[n] << endl;
        if (way[n] != 0) return way[n];
        way[n] = climbStairs_r(n-1, way) + climbStairs_r(n-2, way);
        return way[n];
    }
};

int main()
{
    Solution s;
    {
        timer::auto_cpu_timer t;
        for (int i = 0; i < 1000000; ++i) {
            s.climbStairs(20);
        }
    }
    {
        timer::auto_cpu_timer t;
        for (int i = 0; i < 1000000; ++i) {
            s.climbStairs2(20);
        }
    }
}
