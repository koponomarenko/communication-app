#include "client.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    try {
        Client client;
        client.start();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
