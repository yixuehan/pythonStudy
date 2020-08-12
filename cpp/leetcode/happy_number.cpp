#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/container/flat_set.hpp>
using namespace boost;

template <typename T>
using Set = set<T>;
//using Set = container::flat_set<T>;

class Solution {
public:
    inline int square(int n) {
        int res = 0;
        int x;
        while(n > 0) {
            x = n % 10;
            res += x * x;
            n /= 10;
        }
        return res;
    }
    Set<int> happy;
    Set<int> unhappy;
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = square(slow);
            fast = square(square(fast));
        } while (slow != fast) ;
        return slow == 1;
    }
    bool isHappy3(int n) {
        int slow = n, fast = n;
        do {
            slow = square(slow);
            fast = square(fast);
            fast = square(fast);
        } while (slow != fast) ;
        return slow == 1;
    }

    bool isHappy4(int n) {
        Set<int> s;
        if (happy.find(n) != happy.end()) return true;
        if (unhappy.find(n) != happy.end()) return false;
        while(s.insert(n).second) {
            n = square(n);
            if (happy.find(n) != happy.end()) {
                n = 1;
                break;
            }
            if (unhappy.find(n) != unhappy.end()) {
                n = 0;
                break;
            }
        }
        bool res = (n == 1);
        if (res) {
            happy.insert(s.begin(), s.end());
        }
        else {
            unhappy.insert(s.begin(), s.end());
        }
        return res;
    }
    bool isHappy2(int n) {
        set<int> s;
        while(s.insert(n).second) {
            n = square(n);
        }
        return n == 1;
    }
        
};

int main()
{
    Solution s;
    {
        boost::timer::cpu_timer t;
        for (int i = 0; i < 100000; ++i) {
            s.isHappy(i);
        }
        auto end = t.elapsed();
        cout << boost::timer::format(end) << endl;
    }
    
    {
        boost::timer::cpu_timer t;
        for (int i = 0; i < 100000; ++i) {
            s.isHappy2(i);
        }
        auto end = t.elapsed();
        cout << boost::timer::format(end) << endl;
    }
    
    {
        boost::timer::cpu_timer t;
        for (int i = 0; i < 100000; ++i) {
            s.isHappy3(i);
        }
        auto end = t.elapsed();
        cout << boost::timer::format(end) << endl;
    }
    {
        boost::timer::cpu_timer t;
        for (int i = 0; i < 100000; ++i) {
            s.isHappy4(i);
        }
        auto end = t.elapsed();
        cout << boost::timer::format(end) << endl;
    }
    
}
