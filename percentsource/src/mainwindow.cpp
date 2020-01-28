#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMainWindow>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, percentSender(this) {
  /* Initalize members */
  this->percentSpinBox = new QSpinBox;
  this->percentSpinBox->setMinimum(0);
  this->percentSpinBox->setMaximum(100);
  setCentralWidget(this->percentSpinBox);

  /* View -> Controller signals */
  connect(percentSpinBox, SIGNAL(valueChanged(int)), &percentSender,
          SLOT(setPercent(int)));
}
