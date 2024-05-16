#include "HttpServer.h"

HttpServer::HttpServer(int port) : serverSocket(INVALID_SOCKET), port(port) {}

HttpServer::~HttpServer() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
}

bool HttpServer::start() {
    if (!winsock.isInitialized()) {
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        return false;
    }

    std::cout << "Server is listening on port " << port << std::endl;

    return true;
}

void HttpServer::run() {
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
        return;
    }

    char recvbuf[512];
    int recvbuflen = 512;

    int result = recv(clientSocket, recvbuf, recvbuflen, 0);
    if (result > 0) {
        std::cout << "Received request: " << std::string(recvbuf, result) << std::endl;

        const char* httpResponse =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 2\r\n"
            "\r\n"
            "hi";

        result = send(clientSocket, httpResponse, (int)strlen(httpResponse), 0);
        if (result == SOCKET_ERROR) {
            std::cerr << "send failed: " << WSAGetLastError() << std::endl;
        }
    } else if (result == 0) {
        std::cout << "Connection closing..." << std::endl;
    } else {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }

    closesocket(clientSocket);
}