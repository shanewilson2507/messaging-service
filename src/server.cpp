#include "../include/messaging_service/common.hpp"
#include "../include/messaging_service/network.hpp"
#include "../include/messaging_service/server.hpp"
#include <array>
#include <string>
#include <netinet/in.h>
#include <cstring>

ServerSocket::ServerSocket()
    : Network::Socket(Network::SocketType::SERVER), m_num_connections(0) {
    this -> m_client_addrs.fill(sockaddr_in{});
    memset(&this->m_server_addr, 0, sizeof(this->m_server_addr));
}

void ServerSocket::openSocket(const std::string& address, uint16_t port) {
    if (!this->createSocket()) {
        debug_print("ServerSocket failed to be created");
        return;
    }

    this->m_server_addr.sin_family = AF_INET;
    this->m_server_addr.sin_port = htons(port);

    if (address.empty() || address == "0.0.0.0") {
        this->m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        if (inet_pton(AF_INET, address.c_str(), &this->m_server_addr.sin_addr) != 1) {
            std::cerr<<"Failed to convert resolve IP address: "<< address<<std::endl;
            return;
        }
    }

    if (bind(this->m_socket_FD, (struct sockaddr*) &this->m_server_addr, sizeof(this->m_server_addr)) != 0) {
        std::cerr<<"Error binding server socket: "<<this->m_socket_FD<<std::endl;
        return;
    }

    debug_print("Successfully bound socket: " + std::to_string(this->m_socket_FD) + " to port: " + std::to_string(port));

    if (listen(this->m_socket_FD, MESSAGING_SERVICE_MAX_CONNECTIONS) != 0) {
        std::cerr<<"Socket "<<this->m_socket_FD << " failed to start listening"<< std::endl;
        return;
    } 

    this->m_socket_status = Network::SocketStatus::LISTENING;
    debug_print("Successfully opened socket. Server socket currently listening for connections.");
}

struct sockaddr_in* ServerSocket::getUnoccupiedClientAddr() {
    if (this->m_num_connections >= MESSAGING_SERVICE_MAX_CONNECTIONS) {
        std::cerr << "Max client connections reached on server socket: " << this->m_socket_FD << std::endl;
        return nullptr;
    }
    return &this->m_client_addrs[this->m_num_connections];
}

void ServerSocket::acceptConnections() {
    debug_print("Server socket accepting connections");
    int client_fd;
    struct sockaddr_in* unoccupied_client_addr;
    socklen_t unoccupied_client_addr_len = sizeof(unoccupied_client_addr);
    while (true) {
        unoccupied_client_addr = this->getUnoccupiedClientAddr();
        if (!unoccupied_client_addr) {
            //TODO poll untill ready to accept new connections
            break;
        }
        client_fd = accept(this->m_socket_FD, (struct sockaddr*)unoccupied_client_addr, &unoccupied_client_addr_len);
        if (client_fd < 0){
            std::cerr << "Failed to accept incoming client connection" << std::endl;
        }
        this->m_num_connections++;
        debug_print("Successfully accepted a connection");
        
    }
}



