#ifndef COMMUNICATION_APP_NET1_LISTENER_H
#define COMMUNICATION_APP_NET1_LISTENER_H

#include "IListener.h"

namespace net1 {

class Listener: public IListener {
public:
    void check() const override;
};

}
#endif // COMMUNICATION_APP_NET1_LISTENER_H
