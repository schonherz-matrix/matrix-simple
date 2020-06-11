#include "percentsender.h"

#include <QDebug>
#include <QPoint>
#include <QTimerEvent>
#include <cmath>
#include <thread>

#include "digits.h"

PercentSender::PercentSender(QObject *parent)
    : QObject(parent),
      m_transmitter(MuebTransmitter::getInstance()),
      frame_(32, 26, QImage::Format_RGB888),
      percent_(0),
      flashCount_(0) {
  setPercent(percent_);
  frame_.fill(Qt::black);
  timerID = startTimer(50);
}

void PercentSender::setPercent(int percent) {
  if (flashID) {
    killTimer(flashID);
    flashID = 0;
  }

  if (percent > 100) {
    percent_ = 100;
  } else if (percent < 0) {
    percent_ = 0;
  } else {
    percent_ = percent;
  }
  frame_.fill(Qt::black);

  // First digit
  if (percent_ == 100) {
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 7; y++) {
        // 16
        frame_.setPixelColor(
            x, y, digits[percent_ / 100][y][x] ? Qt::red : Qt::black);
      }
    }
  }

  // Second digit
  if (percent_ >= 10) {
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 7; y++) {
        frame_.setPixelColor(
            x + 4, y, digits[(percent_ / 10) % 10][y][x] ? Qt::red : Qt::black);
      }
    }
  }

  // Third digit
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 7; y++) {
      frame_.setPixelColor(x + 8, y,
                           digits[percent_ % 10][y][x] ? Qt::red : Qt::black);
    }
  }

  // Percent
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 7; y++) {
      frame_.setPixelColor(x + 12, y, digits[10][y][x] ? Qt::red : Qt::black);
    }
  }

  // Filling
  for (int x = 16; x < 24; x++) {
    for (int y = 26 - (26 * percent_ / 100); y < 26; y++) {
      frame_.setPixelColor(x, y, Qt::red);
    }
  }

  // Starting flashTimer if necessary
  if (percent_ == 100) {
    flashCount_ = 0;
    flashID = startTimer(500);
  }
}

void PercentSender::timerEvent(QTimerEvent *event) {
  if (event->timerId() == timerID) {
    m_transmitter.sendFrame(frame_);
  } else {
    if (flashCount_ == 180) {
      for (int x = 16; x < 24; x++) {
        for (int y = 0; y < 26; y++) {
          frame_.setPixelColor(x, y, Qt::red);
        }
      }
    } else {
      if (flashCount_ % 3 == 2) {
        for (int x = 16; x < 24; x++) {
          for (int y = 0; y < 26; y++) {
            frame_.setPixelColor(x, y, Qt::black);
          }
        }
      } else {
        for (int x = 16; x < 24; x++) {
          for (int y = 0; y < 26; y++) {
            frame_.setPixelColor(x, y, Qt::red);
          }
        }
      }
      flashCount_ += 1;
    }
  }
}
