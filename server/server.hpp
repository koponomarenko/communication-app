#ifndef SERVER_HPP_
#define SERVER_HPP_

class Server {
public:
    Server();
    ~Server();

    void start();

private:
    int listener_socket_;
};

#endif
