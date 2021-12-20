#include "Listener.h"

#include <iostream>

namespace net2 {

void Listener::check() const {
    std::cout << "check from net2::Listener" << std::endl;
}

}