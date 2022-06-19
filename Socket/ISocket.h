#pragma once

#include <cstdint>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Socket
{
class ISocket // TCP socket considered
{
public:
    struct Address
    {
        uint32_t ipAddr;
        uint16_t port;
        uint8_t family;
    };

public:
    virtual int socket(int domain, int type, int protocol) = 0;
    virtual int setsockopt(int level, int optname,  const void *optval, uint32_t optlen) const = 0;

    virtual int bind(const struct sockaddr *addr, uint32_t addrlen) const = 0;
    virtual int listen(int backlog) = 0;
    virtual int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) const = 0;

    virtual int connect(const ISocket& sock, const struct sockaddr *addr, uint32_t addrlen) const = 0; 

public:
    int getSockFd() { return _sockfd; }

private:
    int _sockfd;
};
} // namespace Socket