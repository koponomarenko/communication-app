#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>

#include <netinet/in.h>

class Client {
public:
    Client();
    ~Client();

    void start();

private:
    auto get_msg_to_send() -> std::string;
    auto send_msg(const std::string&) -> void;

    int socket_;
    sockaddr_in server_addr_;
};

#endif
