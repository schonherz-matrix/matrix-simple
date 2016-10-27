#include "mainwindow.h"
#include <QMainWindow>
#include <QCoreApplication>
#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {

	/* Initalize members */
	this->percentSender = new PercentSender;
	
	this->percentSpinBox = new QSpinBox;
	this->percentSpinBox->setMinimum(0);
	this->percentSpinBox->setMaximum(100);
	setCentralWidget(this->percentSpinBox);

	/* View -> Controller signals */
	connect(percentSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this->percentSender, &PercentSender::setPercent);
}

MainWindow::~MainWindow(){
	delete percentSender;
}
