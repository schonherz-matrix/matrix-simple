#include "mainwindow.h"
#include <QColorDialog>
#include <QMainWindow>
#include "windowtestsender.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, windowTestSender(this) {
  /* Initalize members */
  numSpinBox = new QSpinBox{this};
  numSpinBox->setMinimum(-100);
  numSpinBox->setMaximum(100);
  numSpinBox->setValue(1);

  /* Setting QSpinBox as central widget */
  setCentralWidget(numSpinBox);

  /* View -> Controller signals */
  connect(numSpinBox, SIGNAL(valueChanged(int)), &windowTestSender,
          SLOT(setSpeed(int)));
}
