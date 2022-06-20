#pragma once

#include <cstdint>
#include <string>
#include <memory>
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

struct Address
{
    std::string ipAddr;
    uint16_t port;
};

class ISocket;
using ISocketUPtr = std::unique_ptr<ISocket>;

class ISocket
{
public:
    virtual ~ISocket() = default;

public:
    // Capitals because name collisions 
    virtual void Bind(Address addr) const = 0;
    virtual void Listen() const = 0;
    virtual void Connect(Address addr) const = 0; 
    virtual ISocketUPtr Accept(Address addr) const = 0;
};
} // namespace Socket