#include "server.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        Server server;
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
