#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muebreceiver.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 public slots:
  void updateFrame(QImage frame);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  QImage frame;
  MUEBReceiver muebreceiver;
  QList<QPoint> coords;
  QImage schView;
};

#endif  // MAINWINDOW_H
