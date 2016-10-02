#include "windowtestsender.h"
#include "array2D.hpp"
#include <cmath>
#include <thread>
#include <exception>
#include <cmath>
#include <QDebug>

WindowTestSender::WindowTestSender()
    : speed_(1)
    , countdown_(1)
    , color_(0)
    , window_(0)
{
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&WindowTestSender::packetCallback, this), std::chrono::milliseconds(50))};
	timer_->start();
}

void WindowTestSender::setSpeed(int speed) {
	m_.lock();
	speed_ = speed;
    countdown_ = abs(speed_);
	m_.unlock();
}

void WindowTestSender::packetCallback() {
	m_.lock();
    if (countdown_ == 0) {
        countdown_ = abs(speed_);
        color_ += 1;
    }
    countdown_--;
    if (color_ == 3) {
        color_ = 0;
        if (speed_ > 0)
            window_ += 1;
        else
            window_ -= 1;
    }
    if (window_ == 32*26 && speed_ > 0) {
        window_ = 0;
    }
    if (window_ == 0 && speed_ < 0) {
        window_ = 32*26-1;
    }
    int x = window_ % 32;
    int y = window_ / 32;
    Color rgb;
    switch (color_) {
        case 0:
            rgb = Color{255, 0, 0};
        break;
        case 1:
            rgb = Color{0, 255, 0};
        break;
        case 2:
            rgb = Color{0, 0, 255};
        break;
        default:
            rgb = Color{255, 255, 255};
        break;
    }
	m_.unlock();
	Frame frame{1};
	frame.pixels = Array2D<Color>(32, 26);
	for (int xi = 0; xi < 32; xi++) {
		for (int yi = 0; yi < 26; yi++) {
            if (xi == x && yi == y) {
                frame.pixels(xi,yi) = rgb;
            } else {
                frame.pixels(xi,yi) = Color{0,0,0};
            }
		}
	}
	transmitter_.sendFrame(frame);
}

WindowTestSender::~WindowTestSender() {
	timer_->stop();
}
