#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

// 避免对 std::pow 重载集消歧义的独有函数
int f(int x, int y)
{
    std::cout << "func thread id:" << std::this_thread::get_id() << "\n";
    return std::pow(x,y);
}

void task_lambda()
{
    std::packaged_task<int(int,int)> task([](int a, int b) {
        std::cout << "labmda thread id:" << std::this_thread::get_id() << "\n";
        return std::pow(a, b);
    });
    std::future<int> result = task.get_future();

    task(2, 9);

    std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind()
{
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();

    task();

    std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread()
{
    std::packaged_task<int(int,int)> task(f);
    std::future<int> result = task.get_future();

    std::thread task_td(std::move(task), 2, 10);

    std::cout << "task_thread:\t" << result.get() << '\n';
    task_td.join();
}

int main()
{
    std::cout << "main thread id:" << std::this_thread::get_id() << "\n";
    task_lambda();
    task_bind();
    task_thread();
}
