#include <iostream>

#include "array2D.hpp"
#include "color.h"
#include "frame.h"

template <typename T>
std::ostream& operator<< (std::ostream& stream, Array2D<T> array)
{
    size_t width, height;
    width = array.getWidth (); height = array.getHeight ();

    stream << "w: " << width << ", h: " << height << std::endl;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x)
            stream << array (x,y) << " ";
        stream << std::endl;
    }

    return stream;
}


std::ostream& operator<< (std::ostream& stream, const Color& color){
    stream << "(" << (int)color.r << "," << (int)color.g << "," << (int) color.b << ")";
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const Frame& frame)
{
    stream << "id: " << frame.id << std::endl << frame.pixels;
    return stream;
}
