#ifndef PERCENT_SENDER_H_INCLUDED
#define PERCENT_SENDER_H_INCLUDED

#include <QColor>
#include <QObject>
#include <string>

#include "muebtransmitter.h"

class PercentSender : public QObject {
  Q_OBJECT

 public:
  PercentSender(QObject *parent = nullptr);
 public slots:
  void setPercent(int percent);

 private:
  libmueb::MuebTransmitter &transmitter_;
  QImage frame_;
  int percent_;
  int flashCount_;
  int timerID = 0;
  int flashID = 0;

  // QObject interface
 protected:
  void timerEvent(QTimerEvent *event) override;
};

#endif
