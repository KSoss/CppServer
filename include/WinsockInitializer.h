#ifndef WINSOCKINITIALIZER_H
#define WINSOCKINITIALIZER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

class WinsockInitializer {
public:
    WinsockInitializer();
    ~WinsockInitializer();
    bool isInitialized() const;

private:
    bool initialized;
};

#endif // WINSOCKINITIALIZER_H