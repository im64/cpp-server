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
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    sockaddr_in address = convertToSockaddr(addr);
    if(bind(static_cast<const int>(_sockfd), (const sockaddr*)&address, sizeof(address)) < 0)
        _state = SocketState::BindingError;
    checkState();
}

void Socket::Listen() const
{
}

ISocketUPtr Socket::Accept(Address addr) const
{
    return nullptr;
}

void Socket::Connect(Address addr) const
{
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