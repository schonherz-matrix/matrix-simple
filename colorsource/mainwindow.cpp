#include "mainwindow.h"
#include <QColorDialog>
#include <QMainWindow>
#include "colorsender.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, colorDialog(this), colorSender(this) {
  /* Setting geometry */
  setGeometry(250, 250, 600, 400);

  /* Setting ColorDialog as central widget */
  setCentralWidget(&colorDialog);

  /* Act as widget, not as a dialog */
  colorDialog.setWindowFlags(Qt::Widget);
  colorDialog.setOptions(QColorDialog::DontUseNativeDialog |
                         QColorDialog::NoButtons);

  /* View -> Controller signals */
  connect(&colorDialog, &QColorDialog::currentColorChanged, &colorSender,
          &ColorSender::setColor);
}
