#pragma once

#include "udpsocket.h"
#include "../common/frame.h"

class MUEBTransmitter {
private:
    std::unique_ptr<UDPSocket> socket_;
    IPAddress4 address_;
    uint16_t port_;
public:
    MUEBTransmitter();
    ~MUEBTransmitter();
    void sendFrame(Frame frame);
};
