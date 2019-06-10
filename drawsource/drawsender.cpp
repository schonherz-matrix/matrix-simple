#include "drawsender.h"
#include <QDebug>
#include <QPoint>
#include <cmath>

DrawSender::DrawSender(QObject* parent)
    : QObject(parent),
      color_{QColor{0, 0, 0}},
      frame_(32, 26, QImage::Format_RGB888),
      transmitter_(this) {
  frame_.fill(Qt::black);
}

void DrawSender::setColor(const QColor& color) { color_ = color; }

void DrawSender::changeCell(const QPoint& cell) {
  int x = cell.x(), y = cell.y();
  if (x < 0 || x >= 32 || y < 0 || y >= 26) return;
  frame_.setPixelColor(x, y, color_);
  transmitter_.sendFrame(frame_);
  emit frameChanged(frame_);
}

void DrawSender::fillFrame() {
  frame_.fill(color_);
  transmitter_.sendFrame(frame_);
  emit frameChanged(frame_);
}
