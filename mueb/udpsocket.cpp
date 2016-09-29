#include "udpsocket.h"

UDPSocket::UDPSocket ()
    : error (NoError)
{
}

void UDPSocket::setAndThrow (UDPSocketException ex)
{
    error = ex.errorType ();
    throw ex;
}

size_t UDPSocket::receive (uint8_t* buffer, size_t size)
{
    IPAddress4 addr;
    uint16_t port;
    return receiveFrom (addr, port, buffer, size);
}

UDPSocketException::UDPSocketException (UDPSocket::Error err, const char* desc) noexcept
    : std::runtime_error (desc), error (err)
{
}

UDPSocket::Error UDPSocketException::errorType () const noexcept 
{
    return error;
}

