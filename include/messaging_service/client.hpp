#ifndef MESSAGING_SERVICE_CLIENT_HPP
#define MESSAGING_SERVICE_CLIENT_HPP

#include "common.hpp"
#include "network.hpp"


class ClientSocket : public Network::Socket {
    private:
        struct sockaddr_in  m_server_addr;
    public:
        //Constructor
        explicit ClientSocket();

        //public member functions
        void openSocket(const std::string& address, uint16_t port) override;
        struct sockaddr_in getAddress() const;
};


#endif //MESSAGING_SERVICE_CLIENT_HPP