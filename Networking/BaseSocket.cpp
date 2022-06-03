#include <iostream>
#include <cstdio>

#include "BaseSocket.h"

namespace Networking
{
BaseSocket::BaseSocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : _address{buildSockAddr(domain, port, interface)}
    , _sock{socket(domain, type, protocol)}
{
    checkError();
}

sockaddr_in BaseSocket::buildSockAddr(int domain, int port, u_long interface) noexcept
{
    sockaddr_in addr;
    addr.sin_family = domain;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(interface);
    return std::move(addr);
}

void BaseSocket::checkError()
{
    if(_sock >= 0) // Success
        return; 

    perror("Unable to create socket");
    exit(EXIT_FAILURE);
}

struct sockaddr_in BaseSocket::getAddress()
{
    return _address;
}

int BaseSocket::getSocket()
{
    return _sock;
}
}