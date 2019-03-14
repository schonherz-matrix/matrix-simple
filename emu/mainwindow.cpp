#include "mainwindow.h"

#include <QBrush>
#include <QFile>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, muebreceiver(this), schView(":/sch.jpg") {
  QFile file(":/schviewcoords.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (!line.length()) break;
    QStringList tmp = line.split(" ");
    coords.append(QPoint(tmp[0].toInt(), tmp[1].toInt()));
  }

  frame.pixels = Array2D<Color>(32, 26);
  for (int x = 0; x < frame.pixels.getWidth(); x++) {
    for (int y = 0; y < frame.pixels.getHeight(); y++) {
      frame.pixels(x, y) = Color{0, 0, 0};
    }
  }

  /* Setting geometry */
  QSize size = schView.size();
  resize(size);
  setFixedSize(size);
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

  /* View -> Controller signals */
  connect(&muebreceiver, &MUEBReceiver::frameChanged, this,
          &MainWindow::updateFrame);
}

void MainWindow::updateFrame(const Frame& f) {
  frame = f;
  update();
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  painter.drawImage(0, 0, schView);

  int wn = 0;
  QPoint tmp;
  foreach (tmp, coords) {
    int x = tmp.x(), y = tmp.y();
    auto bf = frame.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 0);
    auto jf = frame.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 0);
    auto bl = frame.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 1);
    auto jl = frame.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 1);
    painter.setBrush(QBrush(QColor(bf.r, bf.g, bf.b)));
    painter.drawRect(x, y, 8, 8);
    painter.setBrush(QBrush(QColor(jf.r, jf.g, jf.b)));
    painter.drawRect(x + 8, y, 8, 8);
    painter.setBrush(QBrush(QColor(bl.r, bl.g, bl.b)));
    painter.drawRect(x, y + 8, 8, 8);
    painter.setBrush(QBrush(QColor(jl.r, jl.g, jl.b)));
    painter.drawRect(x + 8, y + 8, 8, 8);
    wn++;
  }
}
