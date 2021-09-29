#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>

#include "windowtestsender.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private:
  QSpinBox* numSpinBox;
  WindowTestSender windowTestSender;
};

#endif  // MAINWINDOW_H
