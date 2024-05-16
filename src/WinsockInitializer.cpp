#include "WinsockInitializer.h"

#pragma comment(lib, "Ws2_32.lib")

WinsockInitializer::WinsockInitializer() : initialized(false) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
    } else {
        initialized = true;
    }
}

WinsockInitializer::~WinsockInitializer() {
    if (initialized) {
        WSACleanup();
    }
}

bool WinsockInitializer::isInitialized() const {
    return initialized;
}
