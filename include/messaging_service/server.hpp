#ifndef MESSAGING_SERVICE_SERVER_HPP
#define MESSAGING_SERVICE_SERVER_HPP

#include "common.hpp"
#include "network.hpp"
#include <array>
#include <string>

class ServerSocket : public Network::Socket {
    private:
        struct sockaddr_in m_server_addr;
        std::array<struct sockaddr_in, MESSAGING_SERVICE_MAX_CONNECTIONS> m_client_addrs;
        int m_num_connections;
    public:
        //Constructor
        explicit ServerSocket();

        void openSocket(const std::string& address="0.0.0.0", uint16_t port=MESSAGING_SERVICE_PORT) override;  
        void acceptConnections(); //blocking

    private:
        // returns nullptr on error
        struct sockaddr_in* getUnoccupiedClientAddr();
};

#endif //MESSAGING_SERVICE_SERVER_HPP