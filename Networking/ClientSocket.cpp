#include "ClientSocket.h"

namespace Networking
{
ClientSocket::ClientSocket(int domain, int type, int protocol, int port, u_long interface) noexcept
    : BaseSocket{domain, type, protocol, port, interface}
{}

int ClientSocket::connectToServer(int sock, struct sockaddr_in addr) const
{
    int conn = connect(sock, (struct sockaddr*) &addr, sizeof(addr));
    if (conn >= 0) // Success 
        return conn;

    perror("Unable to bind");
    exit(EXIT_FAILURE);
}
} // namespace Networking