#include "tcp_base.h"

TcpBase::TcpBase(std::string_view host, uint16_t port)
    :_host(host)
    ,_port(port)
{
}

TcpBase::TcpBase(uint16_t port)
    :TcpBase("0.0.0.0", port)
{
}
