#pragma once

#include <cstdint>
#include <iostream>
#include "array2D.hpp"
#include "color.h"

struct Frame {
    int id;
    Array2D<Color> pixels;
};

std::ostream& operator<< (std::ostream& stream, const Frame& frame);
