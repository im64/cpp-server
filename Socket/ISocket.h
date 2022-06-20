#pragma once

#include <cstdint>
#include <unordered_map>

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
    virtual ~ISocket() = default;

public:
    struct Address
    {
        uint32_t ipAddr;
        uint16_t port;
    };

public:
    virtual int setsockopt(int level, int optname,  const void* optval, uint32_t optlen) const = 0;

    virtual int bind(Address addr) const = 0;
    virtual int listen() const = 0;
    virtual int accept(Address addr) const = 0;

    virtual int connect(Address addr) const = 0; 
};
} // namespace Socket