#include "mainwindow.h"
#include <QMainWindow>
#include <QColorDialog>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget* parent): QMainWindow{parent} {
	
	/* Initalize members */
	frameProcessor = std::unique_ptr<FrameProcessor>{new FrameProcessor{}};
	gridDrawer = std::unique_ptr<GridDrawer>{new GridDrawer{this, 32, 26, 20}};
	
	/* Setting geometry */
	setGeometry(250, 250, gridDrawer->sizeHint().width(), gridDrawer->sizeHint().height());

	/* Setting ColorDialog as central widget */
    setCentralWidget(gridDrawer.get());

	/* View -> Controller signals */
	qRegisterMetaType<Frame>("Frame");
    connect(frameProcessor.get(), &FrameProcessor::newFrame, gridDrawer.get(), &GridDrawer::setFrame);
}

MainWindow::~MainWindow(){

}
