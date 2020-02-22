#include "client.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        Client client;
        client.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
