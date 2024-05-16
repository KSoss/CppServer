#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "WinsockInitializer.h"

class HttpServer {
public:
    HttpServer(int port);
    ~HttpServer();
    bool start();
    void run();

private:
    WinsockInitializer winsock;
    SOCKET serverSocket;
    int port;
};

#endif // HTTPSERVER_H