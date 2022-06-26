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
    Socket(Address addr, int sock = -1)
        : _sockfd(sock == -1 ? socket(AF_INET, SOCK_STREAM, 0) : sock)
        , _addr(addr)
    {
        if (_sockfd < 0) exitWithError(SocketError::CreationError);
    }

public:
    // Non copyable, movable 
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket(Socket&& other) = default;
    Socket& operator=(Socket&& other) = default;
    virtual ~Socket();

public:
    // ISocket implementation
    void Bind() const override;
    void Listen() const override;
    void Connect() const override;
    ISocketUPtr Accept() const override;
    void Send(const std::string& data) const override;
    std::string Recieve(std::size_t buffSize) const override;;

private:
    void exitWithError(SocketError errorType) const;
    sockaddr_in addressToSockaddr(const Address addr) const;
    Address sockaddrToAddress(const sockaddr_in addr) const;

private:
    int _sockfd;
    Address _addr; // Either the socket is bound to this addr, or it's connected to this addr
};
} // namespace Socket