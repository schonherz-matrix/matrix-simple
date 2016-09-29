#pragma once

#include "color.h"


class PlayerFrame {
public:
    PlayerFrame();
    PlayerFrame(size_t width, size_t height);
    ~PlayerFrame();
    
    PlayerFrame(const PlayerFrame& other);
    PlayerFrame(PlayerFrame&& other);
    
    PlayerFrame& operator=(const PlayerFrame& other);
    PlayerFrame& operator=(PlayerFrame&& other);  
    
    Color& operator()(size_t x, size_t y);
    const Color& operator()(size_t x, size_t y) const;
    
    void resize(size_t width, size_t height);
    size_t width() const;
    size_t height() const;
private:   
    Color* data;   
    size_t width_, height_;
};
