#ifndef MUEBRECEIVER_H
#define MUEBRECEIVER_H

#include <QObject>
#include <QUdpSocket>

#include "../common/frame.h"

class MUEBReceiver : public QObject {
  Q_OBJECT

  QUdpSocket socket_;
  uint16_t port_;
  Frame frame_;

 public:
  explicit MUEBReceiver(QObject *parent = nullptr, uint16_t port = 10000);

 signals:
  void frameChanged(Frame f);

 public slots:
  void readPendingDatagrams();
};

#endif  // MUEBRECEIVER_H
