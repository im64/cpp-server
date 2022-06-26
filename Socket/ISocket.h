#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

namespace Socket
{
enum class SocketError : std::size_t
{
    CreationError = 0,
    BindingError,
    ListeningError,
    AcceptingError,
    ConnectionError,
    SendingError,
    ReceivingError
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
    // Each name starts with capital to avoid name collisions 
    virtual void Bind() const = 0;
    virtual void Listen() const = 0;
    virtual void Connect() const = 0; 
    virtual ISocketUPtr Accept() const = 0;

    virtual void Send(const std::string& data) const = 0;
    virtual std::string Recieve(std::size_t buffSize = 4096) const = 0;
};
} // namespace Socket