#pragma once

#include <string>
#include <sys/socket.h>


#include "ISocket.h"

namespace Socket // TCP socket considered
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
    Socket(const Socket& other) = delete;
    Socket(Socket&& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket& operator=(Socket&& other) = delete;
    virtual ~Socket(); // Since its base virtual dtor gonna be anyways

public: // ISocket implementation
    int setsockopt(int level, int optname,  const void* optval, uint32_t optlen) const override;
    int bind(Address addr, uint32_t addrlen) const override;
    int listen() const override;
    int accept(Address addr, uint32_t* addrlen) const override;
    int connect(const ISocket& sock, Address addr, uint32_t addrlen) const override;


private:
    void checkState();

private:
    int _sockfd;
    SocketState _state;
};
} // namespace Socket