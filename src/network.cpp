#include "../include/messaging_service/network.hpp"
#include "../include/messaging_service/common.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace Network {

Socket::Socket(SocketType socket_type)
    :   m_socket_status(SocketStatus::DESTROYED), //socket doesn't exist yet
        m_socket_type(socket_type),
        m_socket_FD(-1){ //default for no socket  
}


Socket::~Socket() {
    this->closeSocket();
}


SocketStatus Socket::getSocketStatus() const {
    return this->m_socket_status;
}


SocketType Socket::getSocketType() const {
    return this->m_socket_type;
}


int Socket::getFileDescriptor() const {
    return this->m_socket_FD;
}


bool Socket::createSocket() {
    if (this->m_socket_FD != -1) {
        debug_print("Socket " + std::to_string(this->m_socket_FD) + " already created");
        return false;
    }

    this->m_socket_FD = socket(AF_INET, SOCK_STREAM, 0); //creates an unbound socket
    
    if (this->m_socket_FD == -1) {
        std::cerr<<"Failed to create socket" << std::endl;
        return false;
    }

    this->m_socket_status = SocketStatus::CLOSED;

    debug_print("Socket created: " + std::to_string(this->m_socket_FD));;
    return true;
}


void Socket::closeSocket() {
    if (this->m_socket_FD != -1) {
        int temp = this->m_socket_FD;
        if (close(this->m_socket_FD) == -1) {
            std::cerr<< "Socket " << std::to_string(temp) << " failed to close"<< std::endl;
            return;
        }
        this->m_socket_FD = -1;
        this->m_socket_status = SocketStatus::DESTROYED;
        debug_print("Socket closed: " + std::to_string(temp));
    } else {
        debug_print("Socket already in state DESTROYED");
    }
}


void Socket::sendMessage() {
    //TODO
}


void Socket::recieveMessage() {
    //TODO
}


};//namespace Network