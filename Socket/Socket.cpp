#include <cstdlib>

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
int Socket::bind(Address addr) const
{
    return 42;
}

int Socket::listen() const
{
    return 42;
}

int Socket::accept(Address addr) const
{
    return 42;
}

int Socket::connect(Address addr) const
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