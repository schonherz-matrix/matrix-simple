#include <iostream>

#include "mueb/muebtransmitter.h"

int main() {
    Frame frame{1, {32, 26}};
    for (size_t y = 0; y < frame.pixels.getHeight(); ++y) {
        for (size_t x = 0; x < frame.pixels.getWidth(); ++x)
            frame.pixels(x, y) = {255,128,64};
    }
    MUEBTransmitter transmitter;
    transmitter.sendFrame(frame);
    return 0;
}
