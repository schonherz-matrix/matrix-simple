#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "colorsender.h"
#include <memory>
#include <QMainWindow>
#include <QColorDialog>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	std::unique_ptr<QColorDialog> colorDialog;
    std::unique_ptr<ColorSender> colorSender;
};

#endif // MAINWINDOW_H
