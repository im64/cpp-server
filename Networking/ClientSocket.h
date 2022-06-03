#include "BaseSocket.h"

namespace Networking
{
class ClientSocket final : public BaseSocket
{
public:
    explicit ClientSocket(int domain, int type, int protocol, int port, u_long interface) noexcept;

public:
    ClientSocket(const ClientSocket& other) = delete;
    ClientSocket(ClientSocket&& other) = delete;
    ClientSocket& operator=(const ClientSocket& other) = delete;
    ClientSocket& operator=(ClientSocket&& other) = delete;

public:
    int connectToServer(int sock, struct sockaddr_in addr) const;
};
}