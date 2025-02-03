#include "../include/messaging_service/common.hpp"
#include "../include/messaging_service/client.hpp"


int main(void) {
    ClientSocket client;
    client.openSocket("192.168.1.16",8080);
    ClientSocket client2;
    client2.openSocket("192.168.1.16", 8080);
    return 0;
}