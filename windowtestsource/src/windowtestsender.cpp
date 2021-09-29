#include "windowtestsender.h"

#include <QDebug>

WindowTestSender::WindowTestSender(QObject *parent)
    : QObject(parent),
      transmitter_(libmueb::MuebTransmitter::Instance()),
      speed_(1),
      countdown_(1),
      color_(0),
      window_(0) {
  timerID = startTimer(50);
}

void WindowTestSender::setSpeed(int speed) {
  speed_ = speed;
  countdown_ = abs(speed_);
}

void WindowTestSender::timerEvent(QTimerEvent *) {
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
  if (window_ == 32 * 26 && speed_ > 0) {
    window_ = 0;
  }
  if (window_ == 0 && speed_ < 0) {
    window_ = 32 * 26 - 1;
  }
  int x = window_ % 32;
  int y = window_ / 32;
  QColor rgb;
  switch (color_) {
    case 0:
      rgb.setRgb(255, 0, 0);
      break;
    case 1:
      rgb.setRgb(0, 255, 0);
      break;
    case 2:
      rgb.setRgb(0, 0, 255);
      break;
    default:
      rgb.setRgb(255, 255, 255);
      break;
  }
  QImage frame(32, 26, QImage::Format_RGB888);
  frame.fill(Qt::black);
  frame.setPixelColor(x, y, rgb);
  transmitter_.SendFrame(frame);
}
