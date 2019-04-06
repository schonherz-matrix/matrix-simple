#include "mainwindow.h"

#include <QBrush>
#include <QFile>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent},
      frame(32, 26, QImage::Format_RGB888),
      muebreceiver(this),
      schView(":/sch.jpg") {
  QFile file(":/schviewcoords.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (!line.length()) break;
    QStringList tmp = line.split(" ");
    coords.append(QPoint(tmp[0].toInt(), tmp[1].toInt()));
  }

  frame.fill(Qt::black);

  /* Setting geometry */
  QSize size = schView.size();
  resize(size);
  setFixedSize(size);
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

  /* View -> Controller signals */
  connect(&muebreceiver, &MUEBReceiver::frameChanged, this,
          &MainWindow::updateFrame);
}

void MainWindow::updateFrame(QImage f) {
  frame = f;
  update();
}

void MainWindow::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)

  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  painter.drawImage(0, 0, schView);

  int wn = 0;

  for (auto tmp : coords) {
      int x = tmp.x(), y = tmp.y();

      auto leftTop = frame.pixelColor((wn % 16) * 2 + 0, (wn / 16) * 2 + 0);
      auto rightTop = frame.pixelColor((wn % 16) * 2 + 1, (wn / 16) * 2 + 0);
      auto leftBottom = frame.pixelColor((wn % 16) * 2 + 0, (wn / 16) * 2 + 1);
      auto rigthBottom = frame.pixelColor((wn % 16) * 2 + 1, (wn / 16) * 2 + 1);

      painter.setBrush(leftTop);
      painter.drawRect(x, y, 8, 8);
      painter.setBrush(rightTop);
      painter.drawRect(x + 8, y, 8, 8);
      painter.setBrush(leftBottom);
      painter.drawRect(x, y + 8, 8, 8);
      painter.setBrush(rigthBottom);
      painter.drawRect(x + 8, y + 8, 8, 8);
      wn++;
  }
}
