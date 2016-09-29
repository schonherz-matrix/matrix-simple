#include <iostream>
#include <cstdio>

#include "mueb/muebtransmitter.h"

int main() {
    MUEBTransmitter transmitter;
    uint8_t r, g, b;
    while (scanf("%hhd %hhd %hhd", &r, &g, &b) == 3) {
        Frame frame{1, {32, 26}};
        for (size_t y = 0; y < frame.pixels.getHeight(); ++y) {
            for (size_t x = 0; x < frame.pixels.getWidth(); ++x)
                frame.pixels(x, y) = {r,g,b};
        }
        transmitter.sendFrame(frame);
    }
    return 0;
}
