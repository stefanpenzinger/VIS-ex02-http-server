//
// Created by Philipp Ollmann on 02.12.21.
//

#include "TCPServer_V4.h"

/**
 * Default constructor of IPv4 TCPServer
 * initializes a new Socket with port defined in Constants.h
 */
TCPServer_V4::TCPServer_V4() {
    initializeSocket();
}

/**
 * Constructor of IPv4 TCPServer
 *
 * @param _port (port for communication)
 */
TCPServer_V4::TCPServer_V4(int _port) {
    initializeSocket();
}

/**
 * Deconstruct of IPv4 TCPServer
 */
TCPServer_V4::~TCPServer_V4() {}

/**
 * Creates the socket and set its attributes
 */
void TCPServer_V4::setSocketOptions() {
    mServerAddr.sin_family = AF_INET;
    mServerAddr.sin_port = htons(mCommPort);
    mServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(mServerAddr.sin_zero), '\0', 8);
    mServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

/**
 * Binds the TCPServer to created server
 *
 * @return int (-1 = Error, 0 = Success)
 */
int TCPServer_V4::bind() {
    return ::bind(mServerSocket, (sockaddr*) &mServerAddr, sizeof(mServerAddr));
}

/**
 * Accepts incoming connections
 *
 * @return int (-1 = Error, 0 = Success)
 */
int TCPServer_V4::accept() {
    sockaddr_in clientAddr{};
    socklen_t clientAddrSize = sizeof(clientAddr);
    while(true){
        int commSocket = ::accept(mServerSocket, (sockaddr*)&clientAddr, &clientAddrSize);

        if(commSocket == -1){
            return 0;
        }

        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Connected Socket: " << to_string(commSocket) << endl;
        printClientInfo(&clientAddr);
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

        socketParam* parameter = new socketParam();
        parameter->serverSocket = mServerSocket;
        parameter->clientSocket = commSocket;
        pthread_t threadID;
        int rVal = pthread_create(&threadID, NULL, ClientCommunication, parameter);
    }
}

/**
* Prints information about the connected client
*
* @param clientAddr (address of connected client)
*/
void TCPServer_V4::printClientInfo(sockaddr_in * _clientAddr) {
    struct in_addr ipAddr = _clientAddr->sin_addr;

    char ipAddrStr[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &ipAddr, ipAddrStr, INET_ADDRSTRLEN );

    cout << endl << "IP Address of connected client: " << ipAddrStr << endl;
    cout << "Comm Port of client: " << _clientAddr->sin_port << endl;
}





