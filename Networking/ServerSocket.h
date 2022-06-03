#include "BaseSocket.h"

namespace Networking
{
class ServerSocket final : public BaseSocket 
{
public:
    explicit ServerSocket(int domain, int type, int protocol, int port, u_long interface) noexcept;

public:
    ServerSocket(const ServerSocket& other) = delete;
    ServerSocket(ServerSocket&& other) = delete;
    ServerSocket& operator=(const ServerSocket& other) = delete;
    ServerSocket& operator=(ServerSocket&& other) = delete;

public:
    int bindToNetwork(int sock, struct sockaddr_in addr) const; // openConnection?
};
} // namespace Networking