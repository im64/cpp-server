cmake_minimum_required(VERSION 3.23.2)

project(cpp-server)

add_executable(${PROJECT_NAME} main.cpp Networking/ISocket.cpp)