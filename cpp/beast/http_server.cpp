#include "http_server.h"

Session::Session(boost::asio::ip::tcp::socket &&socket)
    : _stream(std::move(socket))
{
}

Session::~Session()
{
    std::cout << "disconnect\n";
}

void Session::init()
{
    using namespace boost::beast;
    // _buffer = flat_buffer{};
    // _buffer.clear();
    _req = Request{};
    // _req.
    http::async_read(
            _stream,
            _buffer,
            _req,
            boost::beast::bind_front_handler(&Session::do_read, this->shared_from_this())
            );
}

void Session::get_methods(MessageMapPtr methods_ptr)
{
    _get_methods_ptr = methods_ptr;
}

void Session::post_methods(MessageMapPtr methods_ptr)
{
    _post_methods_ptr = methods_ptr;
}

void Session::do_read(const boost::beast::error_code &ec, size_t b)
{
    using namespace boost::beast;
    SPDLOG_INFO("read msg[{}] method[{}] read len[{}]", (const char*)_buffer.data().data(), _req.target().to_string(), b);
    if (ec) {
        SPDLOG_ERROR("read error [{}]", ec.message());
        return;
    }
    SPDLOG_INFO("version[{}] keep_alive[{}]", _req.version(), _req.keep_alive());
    switch (_req.method()) {
    case http::verb::get:
        method_call(_get_methods_ptr);
        break;
    case http::verb::post:
        method_call(_post_methods_ptr);
        break;
    default:
        break;
    }
}

void Session::method_call(MessageMapPtr methods_ptr)
{
    using namespace boost::beast;
    auto iter = methods_ptr->find(_req.target());
    Defer f([&](){
        using namespace std;
        http::write(_stream, _resp);
        if (iter != methods_ptr->end() && _req.keep_alive()) {
            this->init();
        }
            });
    if (methods_ptr->end() == iter) {
        _resp.result(http::status::not_found);
        _resp.set(http::field::version, _req.version());
        return;
    }
    iter->second(_req, _resp);
    _resp.result(http::status::ok);
}

HttpServer::HttpServer(const std::string &host, uint16_t port)
    : _host(host)
    , _port(port)
    , _get_methods_ptr{std::make_shared<MessageMap>()}
    , _post_methods_ptr{std::make_shared<MessageMap>()}
    , _acceptor(_ctx, {boost::asio::ip::make_address(_host), _port})
    , _socket(_ctx)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::get(std::string &&path, MessageCallback cb)
{
    _get_methods_ptr->emplace(path, cb);
}

void HttpServer::post(std::string &&path, MessageCallback cb)
{
    _post_methods_ptr->emplace(path, cb);
}

void HttpServer::run()
{
    do_accept();
    _ctx.run();
}

void HttpServer::listen()
{
}

void HttpServer::do_accept()
{
    _acceptor.async_accept(_socket, [this](const boost::beast::error_code &ec){

        if (!ec) {
            std::cout << "new connection\n";
            auto session_ptr = std::make_shared<Session>(std::move(_socket));
            session_ptr->get_methods(_get_methods_ptr);
            session_ptr->post_methods(_post_methods_ptr);
            session_ptr->init();
        }
        do_accept();
    }
    );

}

/*
Response hello(const Request &req, Response &resp)
{
    using namespace boost::beast;
    SPDLOG_INFO("body {}", req.body());
    
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.set(http::field::keep_alive, req.keep_alive());
    resp.body() = "hello";
    resp.prepare_payload();
    return resp;
}
*/
