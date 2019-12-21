#ifndef COLOR_SENDER_H_INCLUDED
#define COLOR_SENDER_H_INCLUDED

#include <QColor>
#include <QObject>
#include "muebtransmitter.h"

class ColorSender : public QObject {
  Q_OBJECT

  QColor color_;
  MuebTransmitter transmitter_;

 public:
  ColorSender(QObject* parent = nullptr);

 public slots:
  void setColor(const QColor& color);
};

#endif
