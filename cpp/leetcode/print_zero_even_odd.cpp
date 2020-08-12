#include <iostream>
#include <condition_variable>
#include <functional>
#include <thread>
#include <atomic>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;


class ZeroEvenOdd1 {
private:
    int n;
    bool _flag_even{false};
    bool _flag_odd{false};
    int _count{0};
    // mutex _mtx;
    int _nOdd;
    int _nEven;
    // condition_variable _cv;

public:
    ZeroEvenOdd1(int n) {
        this->n = n;
        _nOdd = n - ((n+1) % 2);
        _nEven = n - (n % 2);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n; ++i) {
            // cout << "wait lock zero" << endl;
            // unique_lock<mutex> lck(_mtx);
            // _cv.wait(lck, [&]{return !(_flag_even || _flag_odd);});
            while (_flag_even || _flag_odd)
                this_thread::yield();
            // cout << "zero" << endl;
            printNumber(0);
            ++_count;
            if (_count % 2) {
                _flag_odd = true;
            }
            else {
                _flag_even = true;
            }
            // _cv.notify_all();
        }
        
    }

    void even(function<void(int)> printNumber) {
        // cout << "even:" << count << endl;
        while (_count < _nEven) {
            // cout << "wait lock even" << endl;
            // unique_lock<mutex> lck(_mtx);
            // _cv.wait(lck, [&]{return _flag_even;});
            while (!_flag_even) this_thread::yield();
            // cout << "even:" << _count << endl;
            printNumber(_count);
            _flag_even = false;
            // _cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (_count < _nOdd) {
            // cout << "wait lock odd" << endl;
            // unique_lock<mutex> lck(_mtx);
            // _cv.wait(lck, [&]{return _flag_odd;});
            while (!_flag_odd) this_thread::yield();
            // cout << "odd:" << _count << endl;
            printNumber(_count);
            _flag_odd = false;
            // _cv.notify_all();
        }
    }
};


class ZeroEvenOdd2 {
private:
    int n;
    // atomic<bool> _flag_even{false};
    // atomic<bool> _flag_odd{false};
    // atomic<int> _count{0};
    bool _flag_even{false};
    bool _flag_odd{false};
    int _count{0};
    int _nEven;
    int _nOdd;
    mutex _mtx;
    condition_variable _cv;

public:
    ZeroEvenOdd2(int n) {
        this->n = n;
        _nOdd = n - ((n+1) % 2);
        _nEven = n - (n % 2);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        // printf("wait lock zero\n");
        while (_count < n) {
            unique_lock<mutex> lck(_mtx);
            _cv.wait(lck, [&]{return !(_flag_even || _flag_odd);});
            while (_flag_even || _flag_odd)
                this_thread::yield();
            // cout << "zero" << endl;
            printNumber(0);
            ++_count;
            if (_count % 2) {
                _flag_odd = true;
            }
            else {
                _flag_even = true;
            }
            _cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        // cout << "even:" << count << endl;
        while (_count < _nEven) {
            // printf("wait lock even\n");
            unique_lock<mutex> lck(_mtx);
            _cv.wait(lck, [&]{return _flag_even;});
            while (!_flag_even) this_thread::yield();
            // cout << "even:" << _count << endl;
            printNumber(_count);
            _flag_even = false;
            _cv.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (_count < _nOdd) {
            // printf("wait lock odd\n");
            unique_lock<mutex> lck(_mtx);
            _cv.wait(lck, [&]{return _flag_odd;});
            while (!_flag_odd) this_thread::yield();
            // cout << "odd:" << _count << endl;
            printNumber(_count);
            _flag_odd = false;
            _cv.notify_all();
        }
    }
};

void printNumber(int x) {
    printf("%d", x);
}

void thFunc(function<void(function<void(int)>)> fn, function<void(int)> arg)
{
    // for (int i = 0;i < callTimes; ++i) {
        fn(arg);
    // }
}

using ZeroEvenOdd = ZeroEvenOdd2;

int main()
{
    int callTimes = 2;
    ZeroEvenOdd zeo(callTimes);
    thread t1(thFunc, std::bind(&ZeroEvenOdd::zero, &zeo, std::placeholders::_1), printNumber);
    thread t2(thFunc, std::bind(&ZeroEvenOdd::even, &zeo, std::placeholders::_1), printNumber);
    thread t3(thFunc, std::bind(&ZeroEvenOdd::odd, &zeo, std::placeholders::_1), printNumber);
    t1.join();
    t2.join();
    t3.join();
    printf("\n");
}
