#include "../include/messaging_service/common.hpp"
#include "../include/messaging_service/client.hpp"
#include "../include/messaging_service/server.hpp"

/*
//client script
int main(void) {
    std::cout << "client script started" << std::endl;
    ClientSocket client;
    client.openSocket("127.0.0.1",MESSAGING_SERVICE_PORT);
    return 0;
}
*/


//server script
int main(void ) {
    std::cout << "server script started" << std::endl;
    ServerSocket server;
    server.openSocket();
    server.acceptConnections();
    return 0;
}

