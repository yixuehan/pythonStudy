#include <iostream>
#include <vector>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

class Solution {
public:
    vector<string> fizzBuzz2(int n) {
        vector<string> results;
        results.reserve(n);
        for (int i = 0; i < n; ++i) {
            results.push_back(to_string(i+1));
        }
        for (int i = 2; i < n; i += 3) {
            results[i] = "Fizz";
        }
        for (int i = 4; i < n; i += 5) {
            results[i] = "Buzz";
        }
        for (int i = 14; i < n; i += 15) {
            results[i] = "FizzBuzz";
        }
        return results;
    }
    vector<string> fizzBuzz(int n) {
        vector<string> results;
        results.reserve(n);
        for (int i = 1; i <= n; ++i) {
            if (i % 3 == 0 && i % 5 == 0) {
                results.push_back("FizzBuzz");
            }
            else if(i % 3 == 0) {
                results.push_back("Fizz");
            }
            else if(i % 5 == 0) {
                results.push_back("Buzz");
            }
            else {
                results.push_back(to_string(i));
            }
        }
        return results;
    }
};


template <typename Fn, typename ...Args>
void testElapse(Fn &&func, Args ...args)
{
    timer::auto_cpu_timer t;
    for (int i = 0; i < 10000; ++i) {
        func(std::forward<Args>(args)...);
    }
}

int main()
{
    Solution s;
    testElapse([&]{
           s.fizzBuzz(100); 
            });
    testElapse([&]{
           s.fizzBuzz2(100); 
            });
}
