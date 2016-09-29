#include <iostream>
#include <thread>

#include "mueb/muebreceiver.h"

int main() {
    std::function<void(Frame)> f([](Frame frame) {
        std::cout << frame << std::endl;
    });
    MUEBReceiver receiver(std::move(f));
    return 0;
}
