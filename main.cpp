#include <iostream>
#include <unistd.h>


#include "Socket/Socket.h"

int main()
{
    Socket::ISocketUPtr sock = std::make_unique<Socket::Socket>(Socket::Address{"127.0.0.1", 8093});
    sock->Bind();
    sock->Listen();
    auto acc = sock->Accept();

    auto rcvd = acc->Recieve();

    std::cout << "###########" << std::endl;
    std::cout << rcvd << std::endl;
    std::cout << "###########" << std::endl;
    std::cout << rcvd.size() << " -> " << rcvd.capacity() << std::endl;
    std::cout << "###########" << std::endl;

    std::cout << "Success" << std::endl;
}