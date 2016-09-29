#include "muebreceiver.h"

#include <iostream>


inline static int UpdateFrame(uint8_t* in, Frame& f)
{
    if (in[0] != 0x01) {
        return -1;
    }
    uint8_t PN = in[1]-1;
    if (PN > 4) {
        return -1;
    }
    
    for(int wn = PN * 52, i = 0; wn < (PN+1) * 52; ++wn, ++i)
    {
       auto& bf = f.pixels( (wn%16)*2 + 0, (wn/16)*2 + 0);
       auto& jf = f.pixels( (wn%16)*2 + 1, (wn/16)*2 + 0);
       auto& bl = f.pixels( (wn%16)*2 + 0, (wn/16)*2 + 1);
       auto& jl = f.pixels( (wn%16)*2 + 1, (wn/16)*2 + 1);
       
       bf.r = (in[i*6+0 + 2] & 0xf0) << 1;
       bf.g = (in[i*6+0 + 2] & 0x0f) << 5;
       
       bf.b = (in[i*6+1 + 2] & 0xf0) << 1;
       jf.r = (in[i*6+1 + 2] & 0x0f) << 5;
       
       jf.g = (in[i*6+2 + 2] & 0xf0) << 1;
       jf.b = (in[i*6+2 + 2] & 0x0f) << 5;
       
       bl.r = (in[i*6+3 + 2] & 0xf0) << 1;
       bl.g = (in[i*6+3 + 2] & 0x0f) << 5;
       
       bl.b = (in[i*6+4 + 2] & 0xf0) << 1;
       jl.r = (in[i*6+4 + 2] & 0x0f) << 5;
       
       jl.g = (in[i*6+5 + 2] & 0xf0) << 1;
       jl.b = (in[i*6+5 + 2] & 0x0f) << 5;
    }
    
    return 0;
    
    /*
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
    */
}

MUEBReceiver::MUEBReceiver(std::function<void(Frame)>&& callback) 
    : port_(10000)
    , callback_(std::move(callback))
    , can_run_(true)
    , frame_({1, {32, 26}})
{
    std::unique_ptr<UDPSocket> socket(UDPSocket::create ());
    socket->enableBroadcast (); 
    std::cout << "UDP Socket will receive packets on port "  
              << port_ << std::endl;

    socket->bind({0,0,0,0}, port_);
    
    socket_.swap (socket);
    
    std::unique_ptr<std::thread> thread(new std::thread([this]() {
        std::unique_ptr<uint8_t[]> data( new uint8_t[314] );
        try {
            while (this->can_run_) {
                size_t len;
                IPAddress4 sender_address;
                uint16_t sender_port;
                len = this->socket_->receiveFrom(sender_address, sender_port, data.get(), 314);
                if (len != 314) {
                    std::cerr << "[MUEBReceiver] Ez a csomag rossz meretu FOS!" << std::endl;
                    continue;
                }
                if (UpdateFrame(data.get(), frame_) != 0) {
                    std::cerr << "[MUEBReceiver] Ez a csomag invalid FOS!" << std::endl;
                    continue;
                }
                this->callback_(frame_);
            }
        } catch (...) {
        }
    }));
    thread_.swap(thread);
}

MUEBReceiver::~MUEBReceiver()
{
    if (thread_) {
        thread_->join();
    }
}

void MUEBReceiver::stop() {
    can_run_ = false;
}
