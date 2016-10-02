#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "windowtestsender.h"
#include <memory>
#include <QMainWindow>
#include <QSpinBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSpinBox* numSpinBox;
    std::unique_ptr<WindowTestSender> windowTestSender;
};

#endif // MAINWINDOW_H
