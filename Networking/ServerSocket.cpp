#include "ServerSocket.h"

namespace Networking
{
ServerSocket::ServerSocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : BaseSocket{domain, type, protocol, port, interface}
{}

void ServerSocket::bindToNetwork(int sock, struct sockaddr_in addr)
{
    _conn = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
    if (_conn >= 0) return; // Success 

    perror("Unable to bind");
    exit(EXIT_FAILURE);
}

} // namespace Networking