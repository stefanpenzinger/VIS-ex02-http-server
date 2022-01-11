//
// Created by Philipp Ollmann on 02.12.21.
//
#include "../Constants.h"

#ifndef SOCKETS_TCP_TCPSERVER_V4_H
#define SOCKETS_TCP_TCPSERVER_V4_H

#include "TCPServer.h"

class TCPServer_V4 : public TCPServer {
private:
    /**
     * Address of the server
     */
    sockaddr_in mServerAddr;
    int bind() override;
    int accept() override;
    void setSocketOptions() override;
    void printClientInfo(sockaddr_in * _clientAddr);

public:
    TCPServer_V4();
    TCPServer_V4(int _port);
    ~TCPServer_V4();
};

#endif //SOCKETS_TCP_TCPSERVER_V4_H
