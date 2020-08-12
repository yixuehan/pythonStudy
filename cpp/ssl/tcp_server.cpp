#include "tcp_server.h"
#include "error_code.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>

TcpServer::TcpServer(std::string_view host, uint16_t port)
    :TcpBase(host, port)
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == _sockfd) {
        BOOST_THROW_EXCEPTION("socket");
    }
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(addr);

    if (-1 == bind(_sockfd, reinterpret_cast<sockaddr*>(&addr), len)) {
        BOOST_THROW_EXCEPTION("bind");
    }

    if (-1 == listen(_sockfd, 1024)) {
        throw Fatal("listen");
    }
}

TcpServer::TcpServer(uint16_t port)
    :TcpServer("0.0.0.0", port)
{
}

const std::string_view TcpServer::host() const
{
    return _host;
}

uint16_t TcpServer::port() const
{
    return _port;
}
