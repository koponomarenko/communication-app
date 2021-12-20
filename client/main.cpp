#include "client.h"

#include "IListener.h"
#include "net1/Listener.h"
#include "net2/Listener.h"

#include <iostream>
#include <memory>
#include <stdexcept>

void check_listener(const IListener& listener){
    listener.check();
}

int main()
{
    auto net1_listener = std::make_unique<net1::Listener>();
    auto net2_listener = std::make_unique<net2::Listener>();

    check_listener(*net1_listener);
    check_listener(*net2_listener);

    return 0;

    try {
        Client client;
        client.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
