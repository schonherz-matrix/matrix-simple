#ifndef DRAW_SENDER_H_INCLUDED
#define DRAW_SENDER_H_INCLUDED

#include <QColor>
#include <QImage>
#include <QObject>
#include <string>
#include "muebtransmitter.h"

class DrawSender : public QObject {
  Q_OBJECT

 public:
  explicit DrawSender(QObject* parent = nullptr);
 public slots:
  void setColor(const QColor& color);
  void changeCell(const QPoint& cell);
  void fillFrame();
 signals:
  void frameChanged(QImage frame);

 private:
  QColor color_;
  QImage frame_;
  MuebTransmitter transmitter_;
};

#endif
