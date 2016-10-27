#include "percentsender.h"
#include "array2D.hpp"
#include "digits.h"
#include <thread>
#include <cmath>
#include <QPoint>
#include <QDebug>

PercentSender::PercentSender()
 : frame_(Frame{1})
 , percent_(0)
 , flashCount_(0)
{
    frame_.pixels = Array2D<Color>(32, 26);
    setPercent(percent_);
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&PercentSender::packetCallback, this), std::chrono::milliseconds(50))};
	timer_->start();
}

PercentSender::~PercentSender() {
	timer_->stop();
    if (flashTimer_) {
        flashTimer_->stop();
    }
}

void PercentSender::setPercent(int percent) {
    if (flashTimer_) {
        flashTimer_->stop();
        flashTimer_.reset();
    }
    m_.lock();
        if (percent > 100) {
            percent_ = 100;
        } else if (percent < 0) {
            percent_ = 0;
        } else {
            percent_ = percent;
        }
        frame_.pixels = Array2D<Color>(32, 26);

        /*// First digit
        if (percent_ == 100) {
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 7; y++) {
                    frame_.pixels(x + 16, y) = digits[percent_ / 100][y][x] ? Color{255, 0, 0} : Color{0, 0, 0};
                }
            }
        }
        
        // Second digit
        if (percent_ >= 10) {
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 7; y++) {
                    frame_.pixels(x + 20, y) = digits[(percent_ / 10) % 10][y][x] ? Color{255, 0, 0} : Color{0, 0, 0};
                }
            }
        }
        
        // Third digit
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 7; y++) {
                frame_.pixels(x + 24, y) = digits[percent_ % 10][y][x] ? Color{255, 0, 0} : Color{0, 0, 0};
            }
        }
        
        // Percent
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 7; y++) {
                frame_.pixels(x + 28, y) = digits[10][y][x] ? Color{255, 0, 0} : Color{0, 0, 0};
            }
        }*/
        
        // Filling
        for (int x = 16; x < 24; x++) {
            for (int y = 26 - (26 * percent_ / 100); y < 26; y++) {
                frame_.pixels(x, y) = Color{255, 0, 0};
            }
        }
        
        // Starting flashTimer if necessary
        if (percent_ == 100) {
            flashCount_ = 0;
            flashTimer_ = std::unique_ptr<Timer>{new Timer(std::bind(&PercentSender::flashCallback, this), std::chrono::milliseconds(500))};
            flashTimer_->start();
        }
    m_.unlock();
}


void PercentSender::packetCallback() {
    m_.lock();
    Frame frame = frame_;
    m_.unlock();
    transmitter_.sendFrame(frame);
}

void PercentSender::flashCallback() {
    m_.lock();
    if (flashCount_ == 180) {
        for (int x = 16; x < 24; x++) {
            for (int y = 0; y < 26; y++) {
                frame_.pixels(x, y) = Color{255, 0, 0};
            }
        }
    } else {
        if (flashCount_ % 3 == 2) {
            for (int x = 16; x < 24; x++) {
                for (int y = 0; y < 26; y++) {
                    frame_.pixels(x, y) = Color{0, 0, 0};
                }
            }
        } else {
            for (int x = 16; x < 24; x++) {
                for (int y = 0; y < 26; y++) {
                    frame_.pixels(x, y) = Color{255, 0, 0};
                }
            }
        }
        flashCount_ += 1;
    }
    m_.unlock();
}


