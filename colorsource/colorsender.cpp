#include "colorsender.h"

#include <QDebug>

ColorSender::ColorSender(QObject* parent) : QObject(parent) {}

void ColorSender::setColor(const QColor& color) {
  color_ = color;
  QImage frame(32, 26, QImage::Format_RGB888);
  frame.fill(color_);
  transmitter_.sendFrame(frame);
}
