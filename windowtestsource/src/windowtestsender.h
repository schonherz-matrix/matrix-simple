#ifndef WINDOW_TEST_SENDER_H_INCLUDED
#define WINDOW_TEST_SENDER_H_INCLUDED

#include <QColor>
#include <QObject>

#include "muebtransmitter.h"

class WindowTestSender : public QObject {
  Q_OBJECT

 public:
  explicit WindowTestSender(QObject *parent = nullptr);
 public slots:
  void setSpeed(int speed);

 private:
  MuebTransmitter &m_transmitter;
  int speed_;
  int countdown_;
  int color_;
  int window_;
  int timerID;

  // QObject interface
 protected:
  void timerEvent(QTimerEvent *event) override;
};

#endif
