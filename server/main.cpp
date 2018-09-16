#include "server.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    try {
        Server server;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
