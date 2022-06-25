#include <iostream>
#include <unistd.h>


#include "Socket/Socket.h"

int main()
{
    Socket::ISocketUPtr sock = std::make_unique<Socket::Socket>(Socket::Address{"127.0.0.1", 8091});
    sock->Bind();
    sock->Listen();
    auto acc = sock->Accept();

    char buffer[32000] = {0};
    read(acc->getDescriptor(), buffer, 32000);

    std::cout << "###########" << std::endl;
    std::cout << buffer << std::endl;
    std::cout << "###########" << std::endl;

    std::cout << "Success" << std::endl;
}