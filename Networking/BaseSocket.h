#pragma once

#include <sys/socket.h> 
#include <netinet/in.h>
#include <string>

namespace Networking
{
class BaseSocket
{
public:
    explicit BaseSocket(int domain, int type, int protocol, int port, u_long interface) noexcept;

public:
    BaseSocket(const BaseSocket& other) = delete;
    BaseSocket(BaseSocket&& other) = delete;
    BaseSocket& operator=(const BaseSocket& other) = delete;
    BaseSocket& operator=(BaseSocket&& other) = delete;
    ~BaseSocket() = default; 

public:
    sockaddr_in buildSockAddr(int domain = AF_INET, int port = 8080, u_long interface = INADDR_ANY) noexcept;
    void checkError(); 

private:
    struct sockaddr_in getAddress(); // Consider returning addr as a str or as int. TODO: Review later
    int getSocket();

private:
    int _sock = 0;
    struct sockaddr_in _address;
};
} // namespace Networking