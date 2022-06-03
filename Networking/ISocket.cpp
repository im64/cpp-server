#include <iostream>
#include <cstdio>

#include "ISocket.h"

namespace Networking
{
ISocket::ISocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : _address{buildSockAddr(domain, port, interface)}
    , _sock{socket(domain, type, protocol)}
{
    checkError();
}

sockaddr_in ISocket::buildSockAddr(int domain, int port, u_long interface) noexcept
{
    sockaddr_in addr;
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    return std::move(addr);
}

void ISocket::checkError()
{
    if(_sock >= 0) // Success
        return; 

    perror("Unable to create socket");
    exit(EXIT_FAILURE);
}

struct sockaddr_in ISocket::getAddress()
{
    return _address;
}

int ISocket::getSocket()
{
    return _sock;
}
}