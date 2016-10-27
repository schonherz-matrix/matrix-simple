#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "percentsender.h"
#include <memory>
#include <QMainWindow>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

	private:
		QGraphicsView* centralWidget;
		QHBoxLayout* layout;
		QSpinBox* percentSpinBox;
		PercentSender* percentSender;

	public:
		explicit MainWindow(QWidget* parent = nullptr);
		~MainWindow();

};

#endif // MAINWINDOW_H
