#pragma once

#include <functional>
#include <atomic>
#include <thread>
#include <memory>

#include "udpsocket.h"
#include "../common/frame.h"

class MUEBReceiver {
private:
    std::unique_ptr<UDPSocket> socket_;
    uint16_t port_;
    
    std::function<void(Frame)> callback_;
    
    std::atomic_bool can_run_;
    std::unique_ptr<std::thread> thread_;
    
    Frame frame_;
    
public:
    MUEBReceiver(std::function<void(Frame)>&& callback);
    ~MUEBReceiver();
    void stop();
};
