#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMainWindow>
#include <QPalette>

void MainWindow::setButtonColor(QPushButton& button, const QColor& color) {
  QPalette palette = button.palette();
  palette.setColor(QPalette::Button, color);
  button.setAutoFillBackground(true);
  button.setPalette(palette);
  button.update();
}

void MainWindow::sendAnimChanged() {
  emit animChanged(
      AnimFactory::getAnim(type_, primary_color_, secondary_color_, num_));
}

void MainWindow::selectPrimaryColor() {
  primary_color_ = colorDialog->currentColor();
  setButtonColor(*prColorButton, primary_color_);
  sendAnimChanged();
}

void MainWindow::selectSecondaryColor() {
  secondary_color_ = colorDialog->currentColor();
  setButtonColor(*scColorButton, secondary_color_);
  sendAnimChanged();
}

void MainWindow::selectAnim(const QString& text) {
  for (const auto& it : AnimFactory::AnimTypeString) {
    if (it.first == text.toStdString()) {
      type_ = it.second;
    }
  }
  sendAnimChanged();
}

void MainWindow::selectNum(int num) {
  num_ = num;
  sendAnimChanged();
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, animSender(this) {
  /* Initalize members */
  centralWidget = new QGraphicsView{this};
  layout = new QHBoxLayout{centralWidget};
  colorDialog = new QColorDialog{centralWidget};

  /* Act as widget, not as a dialog */
  colorDialog->setWindowFlags(Qt::Widget);
  colorDialog->setOptions(QColorDialog::DontUseNativeDialog |
                          QColorDialog::NoButtons);
  layout->addWidget(colorDialog);

  sidebar = new QGraphicsView{centralWidget};
  sidebar_layout = new QVBoxLayout{sidebar};

  prColorButton = new QPushButton{"Primary color", sidebar};
  scColorButton = new QPushButton{"Secondary color", sidebar};
  sidebar_layout->addWidget(prColorButton);
  sidebar_layout->addWidget(scColorButton);

  animComboBox = new QComboBox{sidebar};
  for (const auto& it : AnimFactory::AnimTypeString) {
    animComboBox->addItem(QString::fromStdString(it.first));
  }
  sidebar_layout->addWidget(animComboBox);

  numSpinBox = new QSpinBox{sidebar};
  numSpinBox->setMinimum(0);
  numSpinBox->setMaximum(100);
  sidebar_layout->addWidget(numSpinBox);

  layout->addWidget(sidebar);

  /* Setting layout */
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
  setGeometry(250, 250, layout->sizeHint().width(),
              layout->sizeHint().height());

  /* View -> Controller signals */
  connect(prColorButton, &QPushButton::pressed, this,
          &MainWindow::selectPrimaryColor);
  connect(scColorButton, &QPushButton::pressed, this,
          &MainWindow::selectSecondaryColor);
  connect(animComboBox, &QComboBox::currentTextChanged, this,
          &MainWindow::selectAnim);
  connect(numSpinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &MainWindow::selectNum);
  connect(this, &MainWindow::animChanged, &animSender, &AnimSender::setAnim);
}
