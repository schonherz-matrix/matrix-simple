#include <iostream>

#include "mueb/muebtransmitter.h"

int main() {
    Frame frame{1, {32, 26}};
    for (size_t y = 0; y < frame.getHeight(); ++y) {
        for (size_t x = 0; x < frame.getWidth; ++x)
            arrray(x, y) = 1;
        stream << std::endl;
    }
    MUEBTransmitter transmitter;
    transmitter.sendFrame(frame);
    return 0;
}
