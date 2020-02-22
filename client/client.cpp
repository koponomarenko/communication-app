#include "client.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int port_number{3425};
const int server_ip{INADDR_LOOPBACK};

Client::Client()
    : socket_(0)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port_number);
    server_addr_.sin_addr.s_addr = htonl(server_ip);

    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
        throw std::runtime_error{"can't create socket"};
    }
}

Client::~Client() { close(socket_); }

void Client::start()
{
    if (connect(socket_, reinterpret_cast<sockaddr*>(&server_addr_),
                sizeof(server_addr_)) < 0) {
        throw std::runtime_error{"can't connect to the server"};
    }

    while (true) {
        auto msg{get_msg_to_send()};
        send_msg(msg);
    }
}

auto Client::get_msg_to_send() -> std::string
{
    std::string msg;
    std::getline(std::cin, msg);

    return msg;
}

auto Client::send_msg(const std::string& msg) -> void
{
    if (send(socket_, msg.data(), msg.length(), 0) < 0) {
        throw std::runtime_error{"can't send data to the server"};
    }
}
