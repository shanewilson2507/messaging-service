#include "../include/messaging_service/common.hpp"
#include "../include/messaging_service/client.hpp"

ClientSocket::ClientSocket()
    : Network::Socket(Network::SocketType::CLIENT) {
}


void ClientSocket::openSocket(const std::string& address, uint16_t port) {
    if(!this->createSocket()) {
        debug_print("ClientSocket failed to be created");
        return;
    } 
    memset(&this->m_server_addr, 0, sizeof(this->m_server_addr));
    this->m_server_addr.sin_family = AF_INET;
    this->m_server_addr.sin_port  = htons(port);
    if (inet_pton(AF_INET, address.c_str(), &this->m_server_addr.sin_addr) != 1) {
        std::cerr<<"Failed to convert resolve IP address: "<< address<<std::endl;
        return;
    }

    if (connect(this->m_socket_FD,(struct sockaddr*) &this->m_server_addr, sizeof(this->m_server_addr)) == -1) {
        std::cerr<<"Failed to connect socket: "<< this->m_socket_FD<<std::endl;
        return;
    }

    this->m_socket_status = Network::SocketStatus::OPEN;

    debug_print(std::string("Successfully opened socket: ") + std::to_string(this->m_socket_FD));
}

struct sockaddr_in ClientSocket::getAddress() const {
    return this->m_server_addr;
}