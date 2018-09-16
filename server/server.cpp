#include "server.hpp"

#include <stdexcept>
#include <iostream>

#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace {
const int port_number = 3425;
}

Server::Server() : listener_socket_(0)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_number);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    listener_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_socket_ < 0)
    {
        throw std::runtime_error{"can't create socket"};
    }

    if (bind(listener_socket_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        throw std::runtime_error{"can't bind ip address to the socket"};
    }
}

Server::~Server()
{
    close(listener_socket_);
}

void Server::start()
{
    const int backlog_length = 1;
    if (listen(listener_socket_, backlog_length) < 0)
    {
        throw std::runtime_error{"can't mark server socket as listener"};
    }

    int client_socket = accept(listener_socket_, nullptr, nullptr);
    if (client_socket < 0)
    {
        throw std::runtime_error{"can't accept a connection on listener socket"};
    }

    char recv_buffer[1024] = {};
    ssize_t msg_length = recv(client_socket, recv_buffer, sizeof(recv_buffer), 0);
    if (msg_length <= 0)
    {
        close(client_socket);
        throw std::runtime_error{"client sock failed on 'recv'"};
    }
    close(client_socket);

    std::cout << "received message: " << recv_buffer << std::endl;
}
