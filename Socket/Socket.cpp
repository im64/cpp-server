#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "Socket.h"

namespace
{
using namespace Socket;
static const std::unordered_map<SocketError, std::string> errorMessages
{
    {SocketError::CreationError,    "socket() failed"},
    {SocketError::BindingError,     "Bind() failed"},
    {SocketError::ListeningError,   "Listen() failed"},
    {SocketError::AcceptingError,   "Accept() failed"},
    {SocketError::ConnectionError,  "Connect() failed"},
    {SocketError::SendingError,     "Send() failed"},
    {SocketError::ConnectionError,  "Receive() failed"},
};

} // namespace

namespace Socket
{
void Socket::Bind() const
{
    sockaddr_in address = addressToSockaddr(_addr);
    std::cout << _addr.ipAddr << ":" << _addr.port << std::endl;
    if(bind(_sockfd, (const sockaddr*)&address, sizeof(address)) < 0)
        exitWithError(SocketError::BindingError);
}

void Socket::Listen() const
{
    if(listen(_sockfd, 10) < 0)
        exitWithError(SocketError::ListeningError);
}

ISocketUPtr Socket::Accept() const
{
    auto address = addressToSockaddr(_addr);
    auto addrlen = sizeof(address);

    int newSockFd = accept(_sockfd, (sockaddr *)&address, (socklen_t*)&addrlen);
    if (newSockFd < 0)
        exitWithError(SocketError::AcceptingError);

    ISocketUPtr newSock = std::make_unique<Socket>(sockaddrToAddress(address), newSockFd);
    return std::move(newSock);
}

void Socket::Connect() const
{
    auto address = addressToSockaddr(_addr);
    if(connect(_sockfd, (sockaddr*) &address, sizeof(address)) < 0)
        exitWithError(SocketError::ConnectionError);
}

void Socket::Send(const std::string& data) const
{
    send(_sockfd, data.c_str(), data.size(), 0);
}

std::string Socket::Recieve(std::size_t buffSize) const
{
    const std::string crlf = "\r\n\r\n";
    char buffer[buffSize];
    std::string res;

    do
    {
        int x = recv(_sockfd, buffer, buffSize, 0);
        buffer[x] = '\0';
        res += buffer;
    }
    while (res.find(crlf) == std::string::npos || res.size() % buffSize != 0);
    return res;
}

void Socket::exitWithError(SocketError errorType) const
{
    perror(errorMessages.at(errorType).c_str());
    exit(EXIT_FAILURE);
}

// test it 
sockaddr_in Socket::addressToSockaddr(const Address addr) const
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(addr.port);
    inet_pton(AF_INET, addr.ipAddr.c_str(), &(address.sin_addr));
    return address;
}

Address Socket::sockaddrToAddress(const sockaddr_in addr) const
{
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
    uint16_t port = ntohs(addr.sin_port);
    return {ip, port};
}

Socket::~Socket()
{
    close(_sockfd);
}
} // namespace Socket