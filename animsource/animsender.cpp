#include "animsender.h"
#include <QDebug>
#include <QPoint>
#include <cmath>

AnimSender::AnimSender(QObject* parent) : QObject(parent) { startTimer(50); }

void AnimSender::setAnim(AnimInterface* anim) {
  anim_ = std::unique_ptr<AnimInterface>{anim};
}

void AnimSender::timerEvent(QTimerEvent* event) {
  if (anim_) {
    QImage f(32, 26, QImage::Format_RGB888);
    f = anim_->nextFrame();
    transmitter_.sendFrame(f);
  }
}
