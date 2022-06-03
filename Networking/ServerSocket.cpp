#include "ServerSocket.h"

namespace Networking
{
ServerSocket::ServerSocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : BaseSocket{domain, type, protocol, port, interface}
{}

int ServerSocket::bindToNetwork(int sock, struct sockaddr_in addr) const
{
    int b = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
    if (b >= 0) // Success 
        return b;

    perror("Unable to bind");
    exit(EXIT_FAILURE);
}

} // namespace Networking