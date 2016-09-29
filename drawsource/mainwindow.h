#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawsender.h"
#include "griddrawer.h"
#include <memory>
#include <QMainWindow>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
	QGraphicsView* centralWidget;
	QHBoxLayout* layout;
	QColorDialog* colorDialog;
	GridDrawer* gridDrawer;
	QPushButton* fillButton;
    DrawSender* drawSender;
};

#endif // MAINWINDOW_H
