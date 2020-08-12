#include <iostream>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>

#include <boost/timer/timer.hpp>
#include <boost/beast.hpp>

#include <spdlog/spdlog.h>

#include "util/defer.h"

using Request = boost::beast::http::request<boost::beast::http::string_body>;
using Response = boost::beast::http::response<boost::beast::http::string_body>;
using MessageCallback = std::function<void (const Request &, Response &)>;
using MessageMap = std::map<boost::beast::string_view, MessageCallback>;
using MessageMapPtr = std::shared_ptr<MessageMap>;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket &&socket);
    void init();
    void get_methods(MessageMapPtr methods_ptr);
    void post_methods(MessageMapPtr methods_ptr);
    ~Session();
private:
    // boost::asio::ip::tcp::socket _socket;
    boost::beast::tcp_stream _stream;
    boost::beast::flat_buffer _buffer;
    boost::beast::http::request<boost::beast::http::string_body> _req;
    boost::beast::http::response<boost::beast::http::string_body> _resp;
    MessageMapPtr _get_methods_ptr;
    MessageMapPtr _post_methods_ptr;
private:
    void do_read(const boost::beast::error_code &ec, size_t b);
    void method_call(MessageMapPtr methods_ptr);
};

class HttpServer
{
public:
public:
    HttpServer(const std::string &host, uint16_t port);
    void get(std::string &&path, MessageCallback cb);
    void post(std::string &&path, MessageCallback cb);
    void run();
    ~HttpServer();
private:
    std::string _host;
    uint16_t _port;
    MessageMapPtr _get_methods_ptr;
    MessageMapPtr _post_methods_ptr;
    boost::asio::io_context _ctx;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;
private:
    void listen();
    void do_accept();
};
