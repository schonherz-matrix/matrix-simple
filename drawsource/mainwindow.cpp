#include "mainwindow.h"
#include <QMainWindow>
#include <QColorDialog>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {

	/* Initalize members */
	drawSender = new DrawSender;
	
	centralWidget = new QGraphicsView{this};
	
	layout = new QHBoxLayout{centralWidget};
	
	colorDialog = new QColorDialog{centralWidget};
	/* Act as widget, not as a dialog */
    colorDialog->setWindowFlags(Qt::Widget);
    colorDialog->setOptions(
		  QColorDialog::DontUseNativeDialog
		| QColorDialog::NoButtons
    );
	layout->addWidget(colorDialog);
	
	fillButton = new QPushButton("&Fill", centralWidget);
	layout->addWidget(fillButton);
	
	gridDrawer = new GridDrawer{centralWidget, 32, 26, 20};
	layout->addWidget(gridDrawer);

	/* Setting layout */
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
	setGeometry(250, 250, layout->sizeHint().width(), layout->sizeHint().height());

	/* View -> Controller signals */
    connect(colorDialog, &QColorDialog::currentColorChanged, drawSender, &DrawSender::setColor);
	connect(gridDrawer, &GridDrawer::clickEvent, drawSender, &DrawSender::changeCell);
	connect(fillButton, &QPushButton::pressed, drawSender, &DrawSender::fillFrame);
	
	/* Controller -> View signals */
	qRegisterMetaType<Frame>("Frame");
	connect(drawSender, &DrawSender::frameChanged, gridDrawer, &GridDrawer::setFrame);
}

MainWindow::~MainWindow(){
	delete drawSender;
}
