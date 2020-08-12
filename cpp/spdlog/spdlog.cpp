#include <iostream>
#include <chrono>
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

void log_error_handle(const std::string &str)
{
    cout << str << endl;
    *(int*)0 = 100;
    assert(false);
    exit(1);
}

int main()
{
    auto daily = spdlog::daily_logger_mt("daily", "logs/app.log", 0, 0);
    spdlog::set_default_logger(daily);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l][%s:%#]%v");
    // spdlog::flush_every(0s);
    spdlog::flush_every(1s);

    while (1) {
        std::this_thread::sleep_for(1s);
        SPDLOG_INFO("test macro info {}", "fmt info");
        SPDLOG_ERROR("test macro info {}", "fmt info");
        SPDLOG_TRACE("test macro info {}", "fmt info");
        SPDLOG_INFO(fmt::format("{:010}", 10));
        SPDLOG_CRITICAL("test critical");
        exit(1);
    }
    spdlog::info("test info");
    spdlog::set_error_handler(log_error_handle);
    spdlog::flush_on(spdlog::level::err);
    // auto daily = make_shared<spdlog::sinks::daily_file_sink_mt("logs/s.log", 0, 0);
    spdlog::set_default_logger(daily);
    // spdlog::set_pattern("%+");
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l][%s:%#]%v");

    SPDLOG_INFO("test macro info {}", "fmt info");
    SPDLOG_INFO("test macro info {}{}", "fmt info");
    SPDLOG_TRACE("test macro info {}", "fmt info");
    SPDLOG_ERROR("test macro info {}", "fmt info");
    SPDLOG_CRITICAL("test critical");
    spdlog::info("test info");

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
