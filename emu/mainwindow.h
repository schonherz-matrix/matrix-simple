#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frame.h"
#include "muebreceiver.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

  Frame frame_;
  int windowSize_;

  MUEBReceiver muebreceiver_;

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 public slots:
  void updateFrame(Frame frame);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent* event) override;
};

#endif  // MAINWINDOW_H
