//
// Created by Philipp Ollmann on 03.12.21.
//

#include "server/TCPServer_V4.h"

/**
 * Checks arguments and starts the TCP server
 *
 * @param _argc (program arguments counter)
 * @param _argv (program arguments: [1] = port)
 * @return int (-1 = Error, 0 = Success)
 */
int main(int _argc, char** _argv) {
    int commPort = DEF_PORT;

    if (_argc >= 2) {
        if (atoi(_argv[1]) > 1024) {
            commPort = atoi(_argv[1]);
        } else {
            cout << "Port is a reserved mPort - falling back to default mPort" << endl;
        }
    }
    else {
        cout << "Error not enough arguments passed - falling back to defaults" << endl <<
                  "Need arguments: [mPort]";
    }

    TCPServer_V4 *server = new TCPServer_V4();
    server->startServer();
    return 0;
}