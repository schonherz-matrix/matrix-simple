#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

#include "ipaddress.h"

class UDPSocketException;

class UDPSocket {
public:
    static UDPSocket* create (); // The definition for this method should be always in the platform dependent cpp file

    virtual bool isValid () const = 0;
    virtual void bind (const IPAddress4 & address, uint16_t port) = 0;
    virtual void sendTo (const IPAddress4 & dest, uint16_t port, const uint8_t* data, size_t size) = 0; 
    virtual size_t receiveFrom (IPAddress4& fromAddr, uint16_t& port, uint8_t* buffer, size_t size) = 0;
    virtual size_t receive (uint8_t* data, size_t size);

    enum Error {
        NoError = 0,

        PermissionError,
        AddressInUseError,
        ResourceError,
        UnsupportedOperationError,
        TimeoutExceededError,

        UnknownError = -1
    };

    Error getError() const;

    virtual void readTimeout (int msecs) = 0;
    virtual void writeTimeout (int msecs) = 0;
    
    virtual void enableBroadcast (bool=true) = 0;

    virtual ~UDPSocket() = default;
protected:
    Error error;
    
    UDPSocket ();
    UDPSocket (const UDPSocket&) = delete;
    UDPSocket& operator= (const UDPSocket&) = delete;
    
    void setAndThrow(UDPSocketException);
};


class UDPSocketException : public std::runtime_error {
    UDPSocket::Error error;
public:
    UDPSocketException (UDPSocket::Error, const char * description) noexcept;
    
    UDPSocket::Error errorType () const noexcept;

    UDPSocketException (const UDPSocketException&) = default;
    UDPSocketException& operator= (const UDPSocketException&) = default;
    ~UDPSocketException() = default;
};
