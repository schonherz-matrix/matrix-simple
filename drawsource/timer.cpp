#include "timer.h"

#include <iostream>

Timer::Timer(std::function<void (void)>&& task, std::chrono::milliseconds interval): task_{task}, interval_{interval}, stop_{false} {}

void Timer::run() {
    std::chrono::high_resolution_clock::time_point before;
    std::chrono::milliseconds function_execution_time;
    while (!stop_) {
        before = std::chrono::high_resolution_clock::now();
        task_();
        function_execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - before);
        if (function_execution_time > interval_) {
//            std::cout << "fucky" << std::endl;
        };
        std::this_thread::sleep_for(interval_ - function_execution_time);
    }
}

void Timer::start() {
    thread_ = std::thread{&Timer::run, this};
}

void Timer::stop() {
    if (!stop_) {
        stop_ = true;
        thread_.join();
    }
}
