#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

#include "udpsocket.h"

class UDPSocket_linux : public UDPSocket {
    int fd;
public:
    virtual bool isValid () const override;
    virtual void bind (const IPAddress4 & address, uint16_t port) override;
    virtual void sendTo (const IPAddress4 & dest, uint16_t port, const uint8_t* data, size_t size) override; 
    virtual size_t receiveFrom (IPAddress4& sender_addr, uint16_t& sender_port, uint8_t* buffer, size_t size) override;
    
    virtual void readTimeout (int msecs) override;
    virtual void writeTimeout (int msecs) override;

    virtual void enableBroadcast (bool=true) override;

    UDPSocket_linux ();
    virtual ~UDPSocket_linux();

protected:
    
    UDPSocket_linux(const UDPSocket&) = delete;
    UDPSocket_linux& operator= (const UDPSocket&) = delete;
};

