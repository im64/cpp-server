#pragma once

#include <sys/socket.h> 
#include <netinet/in.h>
#include <string>

namespace Networking
{
class ISocket
{
public:
    explicit ISocket(int domain, int type, int protocol, int port, u_long interface) noexcept;

public:
    ISocket(const ISocket& other) = delete;
    ISocket(ISocket&& other) = delete;
    ISocket& operator=(const ISocket& other) = delete;
    ISocket& operator=(ISocket&& other) = delete;
    virtual ~ISocket() = default; 

public:
    sockaddr_in buildSockAddr(int domain = AF_INET, int port = 8080, u_long interface = INADDR_ANY) noexcept;

private:
    void checkError(); 
    struct sockaddr_in getAddress(); // Consider returning addr as a str or as int. TODO: Review later
    int getSocket();

private:
    int _sock = 0;
    struct sockaddr_in _address;
};

// TODO: Implement these
class ServerSocket : public ISocket {};
class ClientSocket : public ISocket {};
}