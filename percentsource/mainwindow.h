#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QComboBox>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include "percentsender.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  QGraphicsView* centralWidget;
  QHBoxLayout* layout;
  QSpinBox* percentSpinBox;
  PercentSender percentSender;

 public:
  explicit MainWindow(QWidget* parent = nullptr);
};

#endif  // MAINWINDOW_H
