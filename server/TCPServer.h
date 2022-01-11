//
// Created by Philipp Ollmann on 09.12.21.
//
#include "../Constants.h"

#ifndef SOCKETS_TCP_TCPSERVER_H
#define SOCKETS_TCP_TCPSERVER_H

/**
 * Client and Server socket for thread
 */
struct socketParam {
    int clientSocket;
    int serverSocket;
};

class TCPServer {
protected:
    /**
     * The port on which the server runs
     */
    int mCommPort;
    /**
     * The server socket
     */
    int mServerSocket;

    int listen();
    virtual int bind() = 0;
    virtual int accept() = 0;
    virtual void setSocketOptions() = 0;
    static int sendMessage(char* _msg, int _commSocket);
    static int receiveMessage(int _commSocket, char* _buffer);
    void initializeSocket();
    static void* ClientCommunication (void* _parameter);
    static char* replace_char(char* _str, char _find, char _replace);

public:
    TCPServer();
    TCPServer(int _port);
    virtual ~TCPServer();
    void startServer();
};

#endif //SOCKETS_TCP_TCPSERVER_H
