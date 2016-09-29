#pragma once 

#include <cstdint>

class IPAddress4 
{
    union internal_rep {
        uint8_t  address_8[4];
        uint32_t address_32;
    };
    internal_rep address;

public:
    uint8_t& a; uint8_t& b; uint8_t& c; uint8_t& d;

    IPAddress4 (uint8_t a, uint8_t b, uint8_t c, uint8_t d);
    IPAddress4 ();
    
    IPAddress4 (const IPAddress4&) = default;
    IPAddress4& operator= (const IPAddress4&) = default;

    uint8_t&        operator[] (uint8_t octet);
    const uint8_t&  operator[] (uint8_t octet) const;

    uint32_t get32 () const;
    void set32 (uint32_t);
};

inline IPAddress4::IPAddress4 (uint8_t a_, uint8_t b_, uint8_t c_, uint8_t d_)
    : a(address.address_8[0]), b(address.address_8[1]), c(address.address_8[2]), d(address.address_8[3])
{
    // Network byte order = BigEndian
    address.address_8[0] = a_; 
    address.address_8[1] = b_; 
    address.address_8[2] = c_;
    address.address_8[3] = d_;
}

inline IPAddress4::IPAddress4 () 
    : a(address.address_8[0]), b(address.address_8[1]), c(address.address_8[2]), d(address.address_8[3])
{
    address.address_32 = 0;
}


inline uint8_t& IPAddress4::operator[] (uint8_t octet) 
{
    return address.address_8[octet];
}

inline const uint8_t& IPAddress4::operator[] (uint8_t octet) const
{
    return address.address_8[octet];
}

inline uint32_t IPAddress4::get32 () const 
{
    return address.address_32;
}

inline void IPAddress4::set32 (uint32_t n)
{
    address.address_32 = n;
}
