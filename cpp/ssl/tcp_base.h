#pragma once
#include <string_view>

class TcpBase
{
public:
    TcpBase(std::string_view host, uint16_t port);
    TcpBase(uint16_t port);
protected:
    std::string_view _host;
    uint16_t _port;
    int _sockfd;
};
