

#include "PlayerFrame.h"



PlayerFrame::PlayerFrame() {
    data = nullptr;
}

PlayerFrame::PlayerFrame(size_t width, size_t height) {
    data = new Color[width*height];    
    width_ = width;
    height_ = height;
}
PlayerFrame::~PlayerFrame() {
    delete[] data;
}

PlayerFrame::PlayerFrame(const PlayerFrame& other) {
    width_ = other.width_;
    height_ = other.height_;
    data = new Color[width_*height_];
    for (size_t i=0; i<width_*height_; ++i) {
        data[i] = other.data[i];
    }    
}

PlayerFrame::PlayerFrame(PlayerFrame&& other) {
    width_ = other.width_;
    height_ = other.height_;
    data = other.data;
    other.data = nullptr;
}

PlayerFrame& PlayerFrame::operator=(const PlayerFrame& other) {
    delete[] data;
    data = nullptr;
    
    width_ = other.width_;
    height_ = other.height_;
    data = new Color[width_*height_];
    for (size_t i=0; i<width_*height_; ++i) {
        data[i] = other.data[i];
    }  
}

PlayerFrame& PlayerFrame::operator=(PlayerFrame&& other) {
    delete[] data;
    data = nullptr;   
    
    width_ = other.width_;
    height_ = other.height_;
    data = other.data;
    other.data = nullptr;
}

Color& PlayerFrame::operator()(size_t x, size_t y) {
    return data[x + y*width_];
}

const Color& PlayerFrame::operator()(size_t x, size_t y) const {
    return data[x + y*width_];
}

void PlayerFrame::resize(size_t width, size_t height) {
    delete[] data;
    width_ = width;
    height_ = height;
    data = new Color[width_*height_];
}

size_t PlayerFrame::width() const {
    return width_;
}
size_t PlayerFrame::height() const {
    return height_;
}
