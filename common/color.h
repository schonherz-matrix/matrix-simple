#pragma once

#include <iostream>

class Color {
public:
    uint8_t r, g ,b;
    
    Color ();
    Color (uint8_t r_, uint8_t g_, uint8_t b_);
    Color (const Color&) = default;
    Color& operator= (const Color&) = default;

    Color operator<< (uint8_t offset) const;
    Color operator>> (uint8_t offset) const;

};

inline Color::Color () : r(0), g(0), b(0) {}

inline Color::Color(uint8_t r_, uint8_t g_, uint8_t b_): r(r_), g(g_), b(b_) {}

inline Color Color::operator<< (uint8_t offset) const {
    Color ret;
    ret.r = this->r << offset;
    ret.g = this->g << offset;
    ret.b = this->b << offset;
    return ret;
}

inline Color Color::operator>> (uint8_t offset) const {
    Color ret;
    ret.r = this->r >> offset;
    ret.g = this->g >> offset;
    ret.b = this->b >> offset;
    return ret;
}

std::ostream& operator<< (std::ostream& stream, const Color& color);
