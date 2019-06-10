#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "drawsender.h"
#include "griddrawer.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);

 private:
  QGraphicsView* centralWidget;
  QHBoxLayout* layout;
  QColorDialog* colorDialog;
  GridDrawer* gridDrawer;
  QPushButton* fillButton;
  DrawSender drawSender;
};

#endif  // MAINWINDOW_H
