#ifndef MESSAGING_SERVICE_NETWORK_HPP
#define MESSAGING_SERVICE_NETWORK_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdint.h>
#include "common.hpp"

#define MESSAGING_SERVICE_MAX_CONNECTIONS 5
#define MESSAGING_SERVICE_PORT 6969

namespace Network {

enum class SocketStatus {
    DESTROYED,
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

        bool                createSocket();
        void                closeSocket();
        void                sendMessage();//TODO change signature after message.hpp
        void                recieveMessage(); //TODO change signature after message.hpp

        //pure virtual functions
        virtual void        openSocket(const std::string& address, uint16_t port) = 0;

};//class Socket


};//namespace Network


#endif //#ifndef MESSAGING_SERVICE_NETWORK_HPP