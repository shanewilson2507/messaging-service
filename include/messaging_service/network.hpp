#ifndef MESSAGING_SERVICE_NETWORK_HPP
#define MESSAGING_SERVICE_NETWORK_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>
#include "common.h"

#define MESSAGING_SERVICE_MAX_CONNECTIONS 5

namespace Network {

enum class SocketStatus {
    CLOSED,
    OPEN,
    LISTENING
};

enum class SocketType {
    CLIENT,
    SERVER
};

class Socket {
    protected:
        SocketStatus        m_socket_status;
        SocketType          m_socket_type;
        int                 m_socket_FD;
        struct sockaddr_in  m_socket_addr;


    public:
        //Constructor
        explicit            Socket(SocketType socket_type);
        //Destructor
        virtual             ~Socket();

        //member functions
        SocketStatus        getSocketStatus()     const;
        SocketType          getSocketType()       const;
        int                 getFileDescriptor()   const;
        struct sockaddr_in  getAddress()          const;

        void                createSocket();
        void                closeSocket();
        void                sendMessage();//TODO change signature after message.hpp
        void                recieveMessage(); //TODO change signature after message.hpp

        //pure virtual functions
        virtual void        openSocket(std::string address, uint16_t port) = 0;

};//class Socket


};//namespace Network


#endif //#ifndef MESSAGING_SERVICE_NETWORK_HPP