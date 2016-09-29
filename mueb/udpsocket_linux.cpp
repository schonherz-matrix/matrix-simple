#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <errno.h>
#include <cstring> // strerror
#include <utility>
#include "udpsocket_linux.h"

static UDPSocketException he_socket ();
static UDPSocketException he_bind ();
static UDPSocketException he_sendto ();
static UDPSocketException he_receive ();
static UDPSocketException he_setsockopt();

static struct ::sockaddr_in construct_sockaddr (const IPAddress4 address, uint16_t port);

UDPSocket* UDPSocket::create ()
{
    return new UDPSocket_linux ();
}

UDPSocket_linux::UDPSocket_linux ()
    : fd (-1)
{
    fd = ::socket (AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
        setAndThrow (he_socket ());
}

UDPSocket_linux::~UDPSocket_linux ()
{
    if( isValid ())
        ::close (fd);
}

bool UDPSocket_linux::isValid () const
{
    return fd > 0;
}

void UDPSocket_linux::bind (const IPAddress4 & address, uint16_t port) 
{
    struct ::sockaddr_in myaddr = construct_sockaddr (address, port);
    ::socklen_t myaddr_len = sizeof (myaddr);


    if ( ::bind (fd, reinterpret_cast<struct ::sockaddr*>(&myaddr), myaddr_len) < 0)
        setAndThrow (he_bind ());
}


void UDPSocket_linux::sendTo (const IPAddress4& dest, uint16_t port, const uint8_t* data, size_t size) 
{   
    struct ::sockaddr_in  destaddr = construct_sockaddr (dest, port);
    ::socklen_t destaddr_len = sizeof (destaddr);
    ssize_t sent = ::sendto (fd, data, size, 0, reinterpret_cast<struct ::sockaddr*>(&destaddr), destaddr_len);
    if (sent < 0)
        setAndThrow (he_sendto());
    
}

size_t UDPSocket_linux::receiveFrom (IPAddress4& sender_address, uint16_t& sender_port, uint8_t* buffer, size_t size)
{
    struct ::sockaddr_in senderaddr;
    ::socklen_t senderaddr_len;

    ssize_t received = ::recvfrom (fd, buffer, size, 0, reinterpret_cast<struct ::sockaddr*>(&senderaddr), &senderaddr_len);

    if (received < 0)
        setAndThrow (he_receive());
    
    
    sender_address.set32 (senderaddr.sin_addr.s_addr);
    sender_port = ntohs(senderaddr.sin_port);

    return received;
}
    
void UDPSocket_linux::readTimeout (int msecs)
{   
    if (!isValid ())
    {
        throw UDPSocketException (UDPSocket::UnsupportedOperationError, "Unable to set reading timeout for an invalid socket");
    }

    struct ::timeval tv;
    if (msecs < 0)  msecs = 0;

    tv.tv_sec  = msecs / 1000;
    tv.tv_usec = msecs % 1000;

    if (setsockopt (fd, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const void*>(&tv), sizeof(tv)) == -1)
    {
        throw UDPSocketException (UDPSocket::UnsupportedOperationError, "Unable to set reading timeout for socket");
    }
}

void UDPSocket_linux::writeTimeout (int msecs)
{   
    if (!isValid ())
    {
        throw UDPSocketException (UDPSocket::UnsupportedOperationError, "Unable to set sending timeout for an invalid socket");
    }

    struct ::timeval tv;
    if(msecs<0) msecs = 0;

    tv.tv_sec  = msecs / 1000;
    tv.tv_usec = msecs % 1000;

    if (setsockopt (fd, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const void*>(&tv), sizeof(tv)) == -1)
    {
        throw UDPSocketException (UDPSocket::UnsupportedOperationError, "Unable to set sending timeout for socket");
    }
}


void UDPSocket_linux::enableBroadcast (bool isEnabled)
{
    int en = isEnabled;
    ::socklen_t enlen = sizeof(en);

    if (setsockopt (fd, SOL_SOCKET, SO_BROADCAST, &en, enlen) < 0)
        setAndThrow (he_setsockopt()); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline struct ::sockaddr_in construct_sockaddr (const IPAddress4 address, uint16_t port)
{
    struct ::sockaddr_in myaddr;
    ::memset (reinterpret_cast<char*>(&myaddr), 0, sizeof (myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = address.get32 ();
    myaddr.sin_port = htons(port);
    return std::move (myaddr);
}

inline UDPSocketException he_socket ()
{
    switch (errno)
    {
      default:
        return UDPSocketException (UDPSocket::UnknownError, ::strerror (errno));
    }
}

inline UDPSocketException he_bind ()
{

    switch (errno)
    {
      default:
        return UDPSocketException (UDPSocket::UnknownError, ::strerror (errno));
    }
}

inline UDPSocketException he_sendto ()
{
    switch (errno)
    {
      default:
        return UDPSocketException (UDPSocket::UnknownError, ::strerror (errno));
    }

}

inline UDPSocketException he_receive ()
{

    switch (errno)
    {
      default:
        return UDPSocketException (UDPSocket::UnknownError, ::strerror (errno));
    }
}

inline UDPSocketException he_setsockopt ()
{

    switch (errno)
    {
      default:
        return UDPSocketException (UDPSocket::UnknownError, ::strerror (errno));
    }
}

