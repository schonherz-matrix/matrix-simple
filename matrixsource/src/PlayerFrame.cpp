

#include "PlayerFrame.h"



PlayerFrame::PlayerFrame()
    : data(nullptr)
    , width_(0)
    , height_(0)
{
    data = nullptr;
}

PlayerFrame::PlayerFrame(size_t width, size_t height) {
    data = new QColor[width*height];
    width_ = width;
    height_ = height;
}
PlayerFrame::~PlayerFrame() {
    delete[] data;
}

PlayerFrame::PlayerFrame(const PlayerFrame& other) {
    width_ = other.width_;
    height_ = other.height_;
    data = new QColor[width_*height_];
    if (other.data != nullptr) {
        for (size_t i=0; i<width_*height_; ++i) {
            data[i] = other.data[i];
        }
    }
}

PlayerFrame::PlayerFrame(PlayerFrame&& other) {
    width_ = other.width_;
    height_ = other.height_;
    data = other.data;
    other.data = nullptr;
    other.height_ = 0;
    other.width_ = 0;
}

PlayerFrame& PlayerFrame::operator=(const PlayerFrame& other) {
    delete[] data;
    data = nullptr;
    
    width_ = other.width_;
    height_ = other.height_;
    data = new QColor[width_*height_];
    if (other.data != nullptr) {
        for (size_t i=0; i<width_*height_; ++i) {
            data[i] = other.data[i];
        }
    }
    
    return *this;
}

PlayerFrame& PlayerFrame::operator=(PlayerFrame&& other) {
    delete[] data;
    data = nullptr;   
    
    width_ = other.width_;
    height_ = other.height_;
    data = other.data;
    other.data = nullptr;
    other.height_ = 0;
    other.width_ = 0;
    
    return *this;
}

QColor& PlayerFrame::operator()(size_t x, size_t y) {
    return data[x + y*width_];
}

const QColor& PlayerFrame::operator()(size_t x, size_t y) const {
    return data[x + y*width_];
}

void PlayerFrame::resize(size_t width, size_t height) {
    delete[] data;
    width_ = width;
    height_ = height;
    data = new QColor[width_*height_];
}

size_t PlayerFrame::width() const {
    return width_;
}
size_t PlayerFrame::height() const {
    return height_;
}
