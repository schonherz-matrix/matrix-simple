#include "drawsender.h"
#include "array2D.hpp"
#include <thread>
#include <cmath>
#include <QPoint>
#include <QDebug>

DrawSender::DrawSender(): color_{QColor{0,0,0}} {
	frame_.pixels = Array2D<Color>{32, 26};
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 26; y++) {
			frame_.pixels(x,y) = Color{0,0,0};
		}
	}
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&DrawSender::packetCallback, this), std::chrono::milliseconds(20))};
	timer_->start();
}

DrawSender::~DrawSender() {
	timer_->stop();
}

void DrawSender::setColor(const QColor& color) {
	m_.lock();
	color_= color;
	m_.unlock();
}

void DrawSender::changeCell(const QPoint& cell) {
	m_.lock();
	frame_.pixels(cell.x(), cell.y()) = Color{color_.red(), color_.green(), color_.blue()};
	m_.unlock();
	emit frameChanged(frame_);
}

void DrawSender::fillFrame() {
	m_.lock();
	Color rgb = Color{color_.red(), color_.green(), color_.blue()};
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 26; y++) {
			frame_.pixels(x,y) = rgb;
		}
	}
	m_.unlock();
	emit frameChanged(frame_);
}

void DrawSender::packetCallback() {
	m_.lock();
	Frame frame = frame_;
	m_.unlock();
	transmitter_.sendFrame(frame);
}


