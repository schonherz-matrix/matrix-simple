#include "muebtransmitter.h"

#include <iostream>

MUEBTransmitter::MUEBTransmitter() 
    : address_(10,255,255,255)
{
    std::unique_ptr<UDPSocket> socket(UDPSocket::create ());
    socket->enableBroadcast (); 
    std::cout << "UDP Socket will send frame to "  
              << (int)address_[0] << '.' << (int)address_[1] << '.' << (int)address_[2] << '.' << (int)address_[3] 
              << std::endl;

    port_ = 10000;
    socket_.swap (socket);
}

MUEBTransmitter::~MUEBTransmitter()
{
}

inline static void CreatePackage(Frame f, int PN, uint8_t out[])
{
    out[0] = 0x01;
    out[1] = static_cast<uint8_t>(PN+1);
    for(int wn = PN * 52, i = 0; wn < (PN+1) * 52; ++wn, ++i)
    {
       Color bf, jf,
             bl, jl;

       bf = f.pixels( (wn%16)*2 + 0, (wn/16)*2 + 0);
       jf = f.pixels( (wn%16)*2 + 1, (wn/16)*2 + 0);
       bl = f.pixels( (wn%16)*2 + 0, (wn/16)*2 + 1);
       jl = f.pixels( (wn%16)*2 + 1, (wn/16)*2 + 1);

       out[i*6+0 + 2] = ((bf.r >> 1) & 0x70) | (bf.g >> 5);
       out[i*6+1 + 2] = ((bf.b >> 1) & 0x70) | (jf.r >> 5);
       out[i*6+2 + 2] = ((jf.g >> 1) & 0x70) | (jf.b >> 5);

       out[i*6+3 + 2] = ((bl.r >> 1) & 0x70) | (bl.g >> 5);
       out[i*6+4 + 2] = ((bl.b >> 1) & 0x70) | (jl.r >> 5);
       out[i*6+5 + 2] = ((jl.g >> 1) & 0x70) | (jl.b >> 5);
    }
}

void MUEBTransmitter::sendFrame(Frame frame){
    if (frame.pixels.getHeight () != 26 || frame.pixels.getWidth () != 32)
    {
        std::cerr << "[MUEBTransmitter] Ez a csomag FOS!" << std::endl;
        return;
    }

    
    std::unique_ptr<uint8_t[]> data( new uint8_t[314] );
    
    for (int i = 0; i < 4; i+=1)
    {
        CreatePackage(frame, i, data.get ());
        socket_->sendTo (address_, port_, data.get(), 314);
    }
}

