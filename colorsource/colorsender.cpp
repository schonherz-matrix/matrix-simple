#include "colorsender.h"
#include "array2D.hpp"
#include <thread>
#include <exception>
#include <cmath>
#include <QDebug>

ColorSender::ColorSender(): color_{QColor{0,0,0}} {
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&ColorSender::packetCallback, this), std::chrono::milliseconds(50))};
	timer_->start();
}

void ColorSender::setColor(const QColor& color) {
	m_.lock();
	color_= color;
	m_.unlock();
}

void ColorSender::packetCallback() {
	m_.lock();
	Color rgb = Color{color_.red(), color_.green(), color_.blue()};
	m_.unlock();
	Frame frame{1};
	frame.pixels = Array2D<Color>(32, 26);
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 26; y++) {
			frame.pixels(x,y) = rgb;
		}
	}
	transmitter.sendFrame(frame);
}

ColorSender::~ColorSender() {
	timer_->stop();
}
