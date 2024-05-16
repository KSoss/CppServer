#include "WinsockInitializer.h"
#include "SimpleHttpServer.h"

int main() {
    SimpleHttpServer server(8080);
    if (server.start()) {
        server.run();
    }
    return 0;
}