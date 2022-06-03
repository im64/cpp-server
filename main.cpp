#include <iostream>

#include "Networking/ISocket.h"

#include "main.h"

int main()
{
    std::cout << "Main function" << std::endl;
    Networking::ISocket x(AF_INET, SOCK_STREAM, 0, 8888, INADDR_ANY);
}