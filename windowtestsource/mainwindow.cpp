#include "mainwindow.h"
#include "windowtestsender.h"
#include <QMainWindow>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {
	/* Initalize members */
	numSpinBox = new QSpinBox{this};
    numSpinBox->setMinimum(-100);
	numSpinBox->setMaximum(100);
    numSpinBox->setValue(1);
	windowTestSender = std::unique_ptr<WindowTestSender>(new WindowTestSender{});

	/* Setting QSpinBox as central widget */
    setCentralWidget(numSpinBox);
    
	/* View -> Controller signals */
    connect(numSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), windowTestSender.get(), &WindowTestSender::setSpeed);
}

MainWindow::~MainWindow(){

}
