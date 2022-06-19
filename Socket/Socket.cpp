#include <cstdlib>
#include <unordered_map>

#include "Socket.h"
#include "ISocket.h"

namespace
{
using namespace Socket;
const std::unordered_map<SocketState, std::string> errorMessages
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
int Socket::setsockopt(int level, int optname,  const void* optval, uint32_t optlen) const
{
    return 42;
}

int Socket::bind(Address addr, uint32_t addrlen) const
{
    return 42;
}

int Socket::listen() const
{
    return 42;
}

int Socket::accept(Address addr, uint32_t* addrlen) const
{
    return 42;
}

int Socket::connect(const ISocket& sock, Address addr, uint32_t addrlen) const
{
    return 42;
}

void Socket::checkState()
{
    if(_state == SocketState::OK) return;
    perror(errorMessages.at(_state).c_str());
    exit(EXIT_FAILURE);
}
} // namespace Socket