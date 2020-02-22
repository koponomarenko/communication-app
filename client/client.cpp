#include "client.hpp"

#include <stdexcept>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace {
const int port_number = 3425;
}

Client::Client()
    : socket_(0)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port_number);
    server_addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

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

    const std::string msg{"hello from the client!"};
    if (send(socket_, msg.data(), msg.length(), 0) < 0) {
        throw std::runtime_error{"can't send data to the server"};
    }
}
