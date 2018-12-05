#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
using namespace std;

#include <boost/timer/timer.hpp>

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = distance(first, last);
    if (!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1) / min_per_thread;
    unsigned long const hardware_threads = thread::hardware_concurrency();
    unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;
    vector<T> results(num_threads);
    vector<thread> threads(num_threads-1);
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        advance(block_end, block_size);
        threads[i] = thread(std::move(accumulate_block<Iterator, T>()), block_start, block_end, ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);
    for (auto &t : threads) {
        t.join();
    }
    return accumulate(results.begin(), results.end(), init);
}

int main()
{
    vector<unsigned int> data(4000000);
    cout << "data count:" << data.size() << "\n";
    for (unsigned int i = 0; i < data.size(); ++i) {
        data[i] = i;
    }
    {
        boost::timer::auto_cpu_timer t;
        parallel_accumulate(data.begin(), data.end(), 0);
    }
    {
        boost::timer::auto_cpu_timer t;
        accumulate(data.begin(), data.end(), 0);
    }
}
