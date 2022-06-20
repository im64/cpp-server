#pragma once

#include <string>
#include <sys/socket.h>


#include "ISocket.h"

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
    // Non copyable and non movable
    Socket(const Socket& other) = delete;
    Socket(Socket&& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket& operator=(Socket&& other) = delete;
    virtual ~Socket();

public: // ISocket implementation
    int bind(Address addr) const override;
    int listen() const override;
    int accept(Address addr) const override;
    int connect(Address addr) const override;

private:
    void checkState();

private:
    int _sockfd;
    SocketState _state;
};
} // namespace Socket