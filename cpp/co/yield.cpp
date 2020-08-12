#include <iostream>
#include <coroutine>
#include <optional>
using namespace std;

template <typename T>
struct generator {
    struct promise_type {
        suspend_never initial_suspend() { return {}; }
        suspend_always final_suspend() { return {}; }

        auto yield_value(T v) {
             val.emplace(std::move(v));
             return suspend_always();
        }

        auto get_return_object() { return generator(this); }
        void return_void() {}
        void unhandled_exception() { throw; }

        auto coro() { return coroutine_handle<promise_type>::from_promise(*this); }

        std::optional<T> val;
    };

    generator(generator&& source) : p(std::exchange(source.p, nullptr)) {}
    explicit generator(promise_type* p) :p(p) {}
    ~generator() {
        if (p) p->coro().destroy();
    }

    // 为了实现range based for和iterator，加上这些代码
    struct EndSentinel{};
    auto end() { return EndSentinel(); }
    auto begin() {
        struct Iter {
            bool operator!=(EndSentinel) const { return !p->coro().done(); }
            void operator++() { p->coro().resume(); }
            T& operator*() const { return *p->val; }

            promise_type* p;
        };
        return Iter{p};
    }

    promise_type* p;
};

generator<int> nums()
{
    for (int i = 0; i < 10; ++i) {
        co_yield i;
    }
}

int main()
{
    auto s = nums();
    for (auto i : s) {
        cout << i << endl;
    }
    // cout << format("abcdef {} {} {} {}", 10, "abc", 20, 1.234) << endl;
}
