#include "server.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int port_number{3425};

using std::cerr;
using std::cout;
using std::endl;

Server::Server()
    : listener_socket_(0)
{
    listener_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_socket_ < 0) {
        throw std::runtime_error{"can't create socket"};
    }

    // bind a socket to an address
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_number);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listener_socket_, reinterpret_cast<sockaddr*>(&addr),
             sizeof(addr)) < 0) {
        throw std::runtime_error{"can't bind ip address to the socket"};
    }

    // make a socket listen
    const int max_pending_connections{SOMAXCONN};
    if (listen(listener_socket_, max_pending_connections) < 0) {
        throw std::runtime_error{"can't mark server socket as listener"};
    }

    make_socket_non_blocking(listener_socket_);
}

Server::~Server() { close(listener_socket_); }

void Server::start()
{
    int epoll_fd{epoll_create1(0)};

    epoll_event event;
    event.data.fd = listener_socket_;
    event.events = EPOLLIN; // wait until there is something to read

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener_socket_, &event);

    const int max_events{32};
    while (true) {
        epoll_event events[max_events];
        const int wait_timeout{-1};
        int fds_number = epoll_wait(epoll_fd, events, max_events, wait_timeout);

        for (decltype(fds_number) i = 0; i < fds_number; ++i) {
            const auto sock{events[i].data.fd};

            // add a new client
            if (sock == listener_socket_) {
                auto client_sock{accept(listener_socket_, 0, 0)};
                make_socket_non_blocking(client_sock);
                epoll_event event;
                event.data.fd = client_sock;
                event.events = EPOLLIN;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sock, &event);
            }
            // get data from a client
            else {
                static const int buff_size{1024};
                static char buff[buff_size] = {};

                auto msg_size{recv(sock, buff, buff_size, MSG_NOSIGNAL)};

                if (msg_size == 0 && errno != EAGAIN) {
                    shutdown(sock, SHUT_RDWR);
                    close(sock);
                }
                else if (msg_size > 0) {
                    std::copy(buff, buff + msg_size,
                              std::ostream_iterator<char>(cout, ""));
                    cout << endl;
                }
                else {
                    cerr << __FILE__ << ':' << __func__ << ':' << __LINE__
                         << ": msg_size is '" << msg_size << "'" << endl;
                }
            }
        }
    }
}

auto Server::make_socket_non_blocking(int socket_fd) -> void
{
    auto flags{fcntl(socket_fd, F_GETFL)};
    // TODO: make a log function (file_name, func_name, line_numb)
    if (flags == -1) {
        cerr << __FILE__ << ':' << __func__ << ':' << __LINE__
             << ": can't get flags for socket_fd '" << socket_fd << "'" << endl;
    }
    fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
}
