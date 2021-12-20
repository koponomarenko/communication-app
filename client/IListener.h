#ifndef COMMUNICATION_APP_ILISTENER_H
#define COMMUNICATION_APP_ILISTENER_H

class IListener {
public:
    virtual ~IListener() = default;

    virtual void check() const = 0;
};

#endif // COMMUNICATION_APP_ILISTENER_H
