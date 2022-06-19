#pragma once

#include <cstdint>

namespace Socket
{
class ISocket // TCP socket considered
{
public:
    struct Address
    {
        uint32_t ipAddr;
        uint16_t port;
    };

public:
    virtual int socket(int domain, int type, int protocol) = 0;
    virtual int setsockopt(int level, int optname,  const void* optval, uint32_t optlen) const = 0;

    virtual int bind(Address addr, uint32_t addrlen) const = 0;
    virtual int listen() = 0;
    virtual int accept(int sockfd, Address addr, uint32_t* addrlen) const = 0;

    virtual int connect(const ISocket& sock, Address addr, uint32_t addrlen) const = 0; 

public:
    int getSockFd() { return _sockfd; }

private:
    int _sockfd;
};
} // namespace Socket