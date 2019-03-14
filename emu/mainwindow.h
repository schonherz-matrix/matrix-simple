#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include "frame.h"
#include "muebreceiver.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 public slots:
  void updateFrame(const Frame& frame);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  Frame frame;
  MUEBReceiver muebreceiver;
  QList<QPoint> coords;
  QImage schView;
};

#endif  // MAINWINDOW_H
