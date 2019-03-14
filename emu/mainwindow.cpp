#include "mainwindow.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, muebreceiver_(this) {
  windowSize_ = 20;

  frame_.pixels = Array2D<Color>(32, 26);
  for (int x = 0; x < frame_.pixels.getWidth(); x++) {
    for (int y = 0; y < frame_.pixels.getHeight(); y++) {
      frame_.pixels(x, y) = Color{0, 0, 0};
    }
  }

  /* Setting geometry */
  setFixedSize(20 * 32, 20 * 26);
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

  /* View -> Controller signals */
  connect(&muebreceiver_, &MUEBReceiver::frameChanged, this, &MainWindow::updateFrame);
}

void MainWindow::updateFrame(Frame frame) {
  frame_ = frame;
  update();
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QPainter painter{this};

  for (int x = 0; x < frame_.pixels.getWidth(); x++) {
    for (int y = 0; y < frame_.pixels.getHeight(); y++) {
      painter.setBrush(
          QBrush{QColor{frame_.pixels(x, y).r, frame_.pixels(x, y).g,
                        frame_.pixels(x, y).b}});
      painter.drawRect(windowSize_ * x, windowSize_ * y, windowSize_,
                       windowSize_);
    }
  }
}
