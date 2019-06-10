#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QComboBox>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include "animfactory.h"
#include "animsender.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  QGraphicsView* centralWidget;
  QHBoxLayout* layout;
  QGraphicsView* sidebar;
  QVBoxLayout* sidebar_layout;
  QColorDialog* colorDialog;
  QPushButton *prColorButton, *scColorButton;
  QComboBox* animComboBox;
  QSpinBox* numSpinBox;
  AnimSender animSender;

  QColor primary_color_, secondary_color_;

  AnimFactory::AnimType type_;

  int num_;

  void setButtonColor(QPushButton& button, const QColor& color);
  void sendAnimChanged();
 private slots:
  void selectPrimaryColor();
  void selectSecondaryColor();
  void selectAnim(const QString& text);
  void selectNum(int num);

 public:
  explicit MainWindow(QWidget* parent = nullptr);
 signals:
  void animChanged(AnimInterface* anim);
};

#endif  // MAINWINDOW_H
