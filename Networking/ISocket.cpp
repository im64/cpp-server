#include <cstdio>

#include "ISocket.h"

namespace Networking
{
ISocket::ISocket(int domain, int type, int protocol, int port, u_long interface) noexcept
{
    _address.sin_family = domain;
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = htonl(interface);

    _sock = socket(domain, type, protocol);
    checkError();
}

void ISocket::checkError()
{
    if(_sock >= 0) // Success
        return; 

    perror("Unable to create socket");
    exit(EXIT_FAILURE);
}

// Getters 
struct sockaddr_in ISocket::getAddress()
{
    return _address;
}

int ISocket::getSocket()
{
    return _sock;
}

}