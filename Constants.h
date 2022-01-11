//
// Created by Philipp Ollmann on 02.12.21.
//

#ifndef SOCKETS_TCP_CONSTANTS_H
#define SOCKETS_TCP_CONSTANTS_H

#include <iostream> // cout, cin
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // IPPROTO_TCP, sockaddr_in
#include <unistd.h> // close
#include <arpa/inet.h> // inet_ntop/inet_atop
#include <string.h> // strlen
#include <semaphore.h> // sem_init
#include <vector>
#include <sstream>
#include <chrono>

// Default port
#define DEF_PORT 80
// Default backlog
#define BACKLOG 10
// Default buffer size
#define BUFFER_SIZE 1024
// Default error code
#define ERROR -1
// Default shutdown command
#define SHUTDOWN "shutdown\0"
// Default quit command
#define QUIT "quit\0"
// Default ip address
#define IP_ADDRESS "192.168.18.7"
// Default ipv6 address
#define IP_ADDRESS_V6 "2a03:c100:f307:7200:1c42:9477:75d3:efe7"
// Default ack
#define ACK  { 'A', 'C', 'K', '\0' }

using namespace std;

#endif //SOCKETS_TCP_CONSTANTS_H
