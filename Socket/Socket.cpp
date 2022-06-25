#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Socket.h"

namespace
{
using namespace Socket;
static const std::unordered_map<SocketState, std::string> errorMessages
{
    {SocketState::OK,               "OK"},
    {SocketState::CreationError,    "socket() failed"},
    {SocketState::BindingError,     "bind() failed"},
    {SocketState::ListeningError,   "listen() failed"},
    {SocketState::AcceptingError,   "accept() failed"},
    {SocketState::ConnectionError,  "connect() failed"},
};

} // namespace

namespace Socket
{
void Socket::Bind(Address addr) const
{
    sockaddr_in address = convertToSockaddr(addr);
    if(bind(_sockfd, (const sockaddr*)&address, sizeof(address)) != 0)
        _state = SocketState::BindingError;
    checkState();
}

void Socket::Listen() const
{
    if(listen(_sockfd, 10) != 0)
        _state = SocketState::ListeningError;
    checkState();
}

ISocketUPtr Socket::Accept(Address addr) const
{
    auto address = convertToSockaddr(addr);
    auto addrlen = sizeof(address);

    int newSockFd = accept(_sockfd, (sockaddr *)&address, (socklen_t*)&addrlen);
    if (newSockFd < 0)
        _state = SocketState::AcceptingError;
    checkState();

    ISocketUPtr newSock = std::make_unique<Socket>(newSockFd);
    return std::move(newSock);
}

void Socket::Connect(Address addr) const
{
    // connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    auto address = convertToSockaddr(addr);
    if(connect(_sockfd, (sockaddr*) &address, sizeof(address)) < 0)
        _state = SocketState::ConnectionError;
    checkState();
}

void Socket::checkState() const
{
    if(_state == SocketState::OK) return;
    perror(errorMessages.at(_state).c_str());
    exit(EXIT_FAILURE);
}

// test it 
sockaddr_in Socket::convertToSockaddr(const Address addr) const
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(addr.ipAddr.c_str());
    address.sin_port = htons(addr.port);
    return address;
}


Socket::~Socket()
{
    close(_sockfd);
}
} // namespace Socket