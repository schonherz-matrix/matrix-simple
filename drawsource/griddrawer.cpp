#include "griddrawer.h"
#include <QDebug>
#include <QPainter>

GridDrawer::GridDrawer(QWidget* parent, int x, int y, int windowSize)
    : QWidget{parent},
      x_{x},
      y_{y},
      windowSize_{windowSize},
      frame_(32, 26, QImage::Format_RGB888) {
  frame_.fill(Qt::black);
  setMouseTracking(true);
}

QSize GridDrawer::minimumSizeHint() const {
  return QSize{x_ * windowSize_, y_ * windowSize_};
}

QSize GridDrawer::sizeHint() const {
  return QSize{x_ * windowSize_, y_ * windowSize_};
}

void GridDrawer::setFrame(QImage frame) {
  frame_ = frame;
  update();
}

void GridDrawer::paintEvent(QPaintEvent*) {
  QPainter painter{this};
  for (int x = 0; x < frame_.width(); x++) {
    for (int y = 0; y < frame_.height(); y++) {
      painter.setBrush(frame_.pixelColor(x, y));
      painter.drawRect(windowSize_ * x, windowSize_ * y, windowSize_,
                       windowSize_);
    }
  }
}

QPoint GridDrawer::screenToGrid(const QPoint& p) {
  return QPoint{p.x() / windowSize_, p.y() / windowSize_};
}

void GridDrawer::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    emit clickEvent(screenToGrid(event->pos()));
  }
}
