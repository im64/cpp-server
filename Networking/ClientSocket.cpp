#include "ClientSocket.h"

namespace Networking
{
ClientSocket::ClientSocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : BaseSocket{domain, type, protocol, port, interface}
{}

void ClientSocket::connectToServer(int sock, struct sockaddr_in addr)
{
    _conn = connect(sock, (struct sockaddr*) &addr, sizeof(addr));
    if (_conn >= 0) return; // Success 

    perror("Unable to bind");
    exit(EXIT_FAILURE);
}
} // namespace Networking