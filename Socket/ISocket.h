#pragma once

#include <cstdint>

namespace Socket
{
enum class SocketState : std::size_t
{
    OK = 0,
    CreationError,
    BindingError,
    ListeningError,
    AcceptingError,
    ConnectionError,
};

class ISocket
{
public:
    struct Address
    {
        uint32_t ipAddr;
        uint16_t port;
    };

public:
    virtual int setsockopt(int level, int optname,  const void* optval, uint32_t optlen) const = 0;

    virtual int bind(Address addr, uint32_t addrlen) const = 0;
    virtual int listen() const = 0;
    virtual int accept(Address addr, uint32_t* addrlen) const = 0;

    virtual int connect(const ISocket& sock, Address addr, uint32_t addrlen) const = 0; 
};
} // namespace Socket