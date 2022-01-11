cmake_minimum_required(VERSION 3.20)
project(sockets_tcp)

set(CMAKE_CXX_STANDARD 14)

add_executable(server_1_2_tcp_v4 server_main.cpp server/TCPServer_V4.cpp server/TCPServer_V4.h Constants.h server/TCPServer.cpp server/TCPServer.h)