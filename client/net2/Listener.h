#ifndef COMMUNICATION_APP_NET2_LISTENER_H
#define COMMUNICATION_APP_NET2_LISTENER_H

#include "IListener.h"

namespace net2 {

class Listener: public IListener {
public:
    void check() const override;
};

}

#endif // COMMUNICATION_APP_NET2_LISTENER_H
