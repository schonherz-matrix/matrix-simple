#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "griddrawer.h"
#include "frameprocessor.h"
#include <memory>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	std::unique_ptr<FrameProcessor> frameProcessor;
	std::unique_ptr<GridDrawer> gridDrawer;
};

#endif // MAINWINDOW_H
