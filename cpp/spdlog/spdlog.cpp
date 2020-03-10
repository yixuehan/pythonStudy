#include <iostream>
using namespace std;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
// #include <spdlog/formatter.h>
// #include <spdlog/fmt/fmt.h>
// #include <spdlog/fmt/bundled/format.h>
//

void test_log()
{
    // auto thread_id = std::this_thread::get_id();
    // size_t id = thread_id;
    for (int i = 0; i < 100; ++i) {
        SPDLOG_INFO("thread id no {}", i);
    }
}

int main()
{
    spdlog::flush_every(1s);
    spdlog::set_level(spdlog::level::trace);
    SPDLOG_INFO("test macro info {}", "fmt info");
    SPDLOG_TRACE("test macro info {}", "fmt info");
    SPDLOG_CRITICAL("test critical");
    spdlog::info("test info");
    auto daily = spdlog::daily_logger_mt("daily", "logs/app.log", 0, 0);
    // auto daily = make_shared<spdlog::sinks::daily_file_sink_mt("logs/s.log", 0, 0);
    spdlog::set_default_logger(daily);
    // spdlog::set_pattern("%+");
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l][%s:%#]%v");

    SPDLOG_INFO("test info");
    SPDLOG_DEBUG("test debug");
    size_t thread_count = 10;
    std::thread tds[thread_count] ;
    for (size_t i = 0; i < thread_count; ++i) {
        tds[i] = thread(test_log);
    }
    for (size_t i = 0; i < thread_count; ++i) {
        tds[i].join();
    }
//    getchar();
}
