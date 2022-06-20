#pragma once

#include "ISocket.h"
#include <arpa/inet.h>

/**
 * Implementation of TCP socket for UNIX systems.
 * If you want to use the server under Windows, reimplement this class using winsock
 */
namespace Socket 
{
class Socket final : public ISocket
{
public:
    explicit Socket()
        : _sockfd(socket(AF_INET, SOCK_STREAM, 0))
        , _state(_sockfd < 0 ? SocketState::CreationError : SocketState::OK)
    {
        checkState();
    }

public:
    // Non copyable, movable 
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket(Socket&& other) = default;
    Socket& operator=(Socket&& other) = default;
    virtual ~Socket();

public: // ISocket implementation
    void Bind(Address addr) const override;
    void Listen() const override;
    void Connect(Address addr) const override;
    ISocketUPtr Accept(Address addr) const override;

private:
    void checkState() const;
    sockaddr_in convertToSockaddr(const Address addr) const;

private:
    int _sockfd;
    mutable SocketState _state;
};
} // namespace Socket