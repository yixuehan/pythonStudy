#pragma once
#include "tcp_base.h"

class TcpServer : public TcpBase
{
public:
    TcpServer(std::string_view host, uint16_t port);
    TcpServer(uint16_t port);
    const std::string_view host() const ;
    uint16_t port() const;
private:
};
