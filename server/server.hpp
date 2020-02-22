#ifndef SERVER_HPP_
#define SERVER_HPP_

class Server {
public:
    Server();
    ~Server();

    void start();

private:
    auto make_socket_non_blocking(int socket_fd) -> void;

    int listener_socket_;
};

#endif
