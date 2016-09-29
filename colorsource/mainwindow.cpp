#include "mainwindow.h"
#include "colorsender.h"
#include <QMainWindow>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {
	/* Setting geometry */
	setGeometry(250, 250, 600, 400);
	
	/* Initalize members */
	colorDialog = std::unique_ptr<QColorDialog>{new QColorDialog{this}};
	colorSender = std::unique_ptr<ColorSender>{new ColorSender{}};

	/* Setting ColorDialog as central widget */
    setCentralWidget(colorDialog.get());
    
    /* Act as widget, not as a dialog */
    colorDialog->setWindowFlags(Qt::Widget);
    colorDialog->setOptions(
		  QColorDialog::DontUseNativeDialog
		| QColorDialog::NoButtons
    );

	/* View -> Controller signals */
    connect(colorDialog.get(), &QColorDialog::currentColorChanged, colorSender.get(), &ColorSender::setColor);  
}

MainWindow::~MainWindow(){

}
