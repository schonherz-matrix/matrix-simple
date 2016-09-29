#include "animsender.h"
#include "array2D.hpp"
#include <thread>
#include <cmath>
#include <QPoint>
#include <QDebug>

AnimInterface::~AnimInterface() {}

AnimSender::AnimSender() {
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&AnimSender::packetCallback, this), std::chrono::milliseconds(50))};
	timer_->start();
}

AnimSender::~AnimSender() {
	timer_->stop();
}

void AnimSender::setAnim(AnimInterface* anim) {
	m_.lock();
	anim_ = std::unique_ptr<AnimInterface>{anim};
	m_.unlock();
}

void AnimSender::packetCallback() {
	if (anim_) {
		m_.lock();
		Frame f;
		f = anim_->nextFrame();
		m_.unlock();
		transmitter_.sendFrame(f);
	}
}


