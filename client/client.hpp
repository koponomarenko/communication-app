#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <netinet/in.h>

class Client
{
public:
    Client();
    ~Client();

    void start();

private:
    int socket_;
    sockaddr_in server_addr_;
};

#endif
