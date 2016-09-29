#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
                                                                                                
#include <thread>                                                                                           
#include <atomic>                                                                                           
#include <chrono>                                                                                           
#include <functional>                                                                                       
                                                                                                
class Timer {
    private:
        std::function<void (void)> task_;
        std::chrono::milliseconds interval_;
        std::thread thread_;
        std::atomic<bool> stop_;
        void run();
    public:
        Timer(std::function<void (void)>&& task, std::chrono::milliseconds interval);
        void start();
        void stop();
};

#endif
