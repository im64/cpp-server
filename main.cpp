#include <iostream>

#include "Socket/Socket.h"

int main()
{
    Socket::ISocketUPtr sock = std::make_unique<Socket::Socket>();
    sock->Bind({"127.0.0.1", 8090});
    sock->Listen();
    std::cout << "Success" << std::endl;
}