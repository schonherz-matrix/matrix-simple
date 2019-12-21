#ifndef DRAW_SENDER_H_INCLUDED
#define DRAW_SENDER_H_INCLUDED

#include <QColor>
#include <QObject>
#include <string>
#include "muebtransmitter.h"

class AnimInterface {
 public:
  virtual QImage nextFrame() = 0;
};

class AnimSender : public QObject {
  Q_OBJECT

 public:
  AnimSender(QObject* parent = nullptr);
 public slots:
  void setAnim(AnimInterface* anim);

 private:
  std::unique_ptr<AnimInterface> anim_;
  MuebTransmitter transmitter_;

  // QObject interface
 protected:
  void timerEvent(QTimerEvent* event) override;
};

#endif
