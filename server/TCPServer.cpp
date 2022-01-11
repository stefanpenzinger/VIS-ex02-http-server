//
// Created by Philipp Ollmann on 09.12.21.
//

#include <algorithm>
#include "TCPServer.h"

/**
 * Default Constructor of TCPServer
 * Sets the port to DEF_PORT (defined in Constants.h)
 */
TCPServer::TCPServer() {
    mCommPort = DEF_PORT;
}

/**
 * Constructor of TCPServer
 *
 * @param _port (port for communication)
 */
TCPServer::TCPServer(int _port) {
    mCommPort = _port;
}

/**
 * Destructor of TCPServer
 */
TCPServer::~TCPServer() {}

/**
 * Initializes the socket
 * sets socket Options and binds the socket
 */
void TCPServer::initializeSocket() {
    //setSocketOptions
    setSocketOptions();
    // bind
    bind();
}

/**
 * Starts the TCPServer
 * Starts listening for incoming connections
 */
void TCPServer::startServer() {
    if(listen() == ERROR){
        std::cout << "Server: Listening went wrong!" << std::endl;
    } else {
        std::cout << "Server: Listening for connections..." << std::endl;
        accept();
    }
}

/**
 * Thread handled Client communication
 *
 * @param _parameter (static socketParam so more than 1 argument can be passed)
 * @return
 */
void *TCPServer::ClientCommunication(void *_parameter) {

    socketParam* p = (socketParam *) _parameter;
    int clientSocket = p->clientSocket;
    int serverSocket = p->serverSocket;
    char buffer[BUFFER_SIZE] = {};

    while (true) {
        int rv = receiveMessage(clientSocket, buffer);
        std::cout << "Message received (Socket: " << to_string(clientSocket) << ") : " << buffer << std::endl;

        if(rv <= 0){
            return 0;
        }

        sendMessage(buffer, clientSocket);
        std::cout << "-----------------------------------------" << std::endl;

        //check for shutdown
        if(::strcmp(buffer, SHUTDOWN) == 0){
            int rv = receiveMessage(clientSocket, buffer);
            if(::strcmp(buffer, "Echo Echo shutdown") == 0){
                close(serverSocket);
                std::cout << "Shutdown..." << std::endl;
                return 0;
            }
        }
    }
}

/**
 * Listen to incoming connections
 *
 * @return int (-1 = error, 0 = success)
 */
int TCPServer::listen() {
    return ::listen(mServerSocket, BACKLOG);
}

/**
 * Receives a message from the connected client
 *
 * @param _commSocket int (socket where message is received)
 * @param _buffer char* (buffer to fill with received message)
 * @return int (-1 = Error, 0 = connection Lost to Client, >0 = received bytes)
 */
 int TCPServer::receiveMessage(int _commSocket, char * _buffer) {
    int rVal = recv(_commSocket, _buffer, BUFFER_SIZE, 0);

    if (rVal == ERROR) {
        perror("ERROR: An error occured while receiving the message");
    }
    else if (rVal == 0) {
        const string error = "ERROR: Connection lost to client (Socket: " + to_string(_commSocket) + ")";
        perror(error.data());
    }
    else {
        _buffer[rVal] = '\0';
    }

    return rVal;
}

/**
 * Sends a message to the connected client
 *
 * @param _msg char* (message to send)
 * @param _commSocket int (socket to send message)
 * @return int (-1 = error, 0 = success)
 */
 int TCPServer::sendMessage(char * _msg, int _commSocket) {
    char echo[BUFFER_SIZE] = {};

    string s = _msg;
    string from = "\n";
    string to = "\r\n";


    size_t start_pos = 0;
    while((start_pos = s.find(from, start_pos)) != std::string::npos) {
        s.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }

    string message =  "HTTP/1.1 200 Okay\r\nContent-Type: text/html; charset=ISO-8859-4 \r\n\r\n<body><h1>Browser Request</h1>";
    message.append(s);
    message.append("</body>");

    int msgSize = message.size(); // check size!
    std::cout << "Sending answer: " << message << std::endl;
    return ::send(_commSocket, &message[0], msgSize, 0);
}

char* TCPServer::replace_char(char* _str, char _find, char _replace) {
    char *current_pos = strchr(_str, _find);
    while (current_pos) {
        *current_pos = _replace;
        current_pos = strchr(current_pos, _find);
    }
    return _str;
}
