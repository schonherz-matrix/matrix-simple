#include "muebreceiver.h"

#include <QNetworkDatagram>

inline static int UpdateFrame(uint8_t *in, Frame &f) {
  if (in[0] != 0x01) {
    return -1;
  }
  uint8_t PN = in[1] - 1;
  if (PN > 4) {
    return -1;
  }

  for (int wn = PN * 52, i = 0; wn < (PN + 1) * 52; ++wn, ++i) {
    auto &bf = f.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 0);
    auto &jf = f.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 0);
    auto &bl = f.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 1);
    auto &jl = f.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 1);

    bf.r = (in[i * 6 + 0 + 2] & 0xf0) << 1;
    bf.g = (in[i * 6 + 0 + 2] & 0x0f) << 5;

    bf.b = (in[i * 6 + 1 + 2] & 0xf0) << 1;
    jf.r = (in[i * 6 + 1 + 2] & 0x0f) << 5;

    jf.g = (in[i * 6 + 2 + 2] & 0xf0) << 1;
    jf.b = (in[i * 6 + 2 + 2] & 0x0f) << 5;

    bl.r = (in[i * 6 + 3 + 2] & 0xf0) << 1;
    bl.g = (in[i * 6 + 3 + 2] & 0x0f) << 5;

    bl.b = (in[i * 6 + 4 + 2] & 0xf0) << 1;
    jl.r = (in[i * 6 + 4 + 2] & 0x0f) << 5;

    jl.g = (in[i * 6 + 5 + 2] & 0xf0) << 1;
    jl.b = (in[i * 6 + 5 + 2] & 0x0f) << 5;
  }

  return 0;
}

MUEBReceiver::MUEBReceiver(QObject *parent, uint16_t port)
    : QObject(parent), socket_(this), port_(port), frame_({1, {32, 26}}) {
  qInfo() << "UDP Socket will receive packets on port" << port_;

  socket_.bind(port_);

  connect(&socket_, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void MUEBReceiver::readPendingDatagrams() {
  size_t len = 0;
  std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(314);
  QHostAddress sender_address;
  uint16_t sender_port;
  while (socket_.hasPendingDatagrams()) {
    len = this->socket_.readDatagram(reinterpret_cast<char *>(data.get()), 314,
                                     &sender_address, &sender_port);

    if (len != 314) {
      qWarning() << "[MUEBReceiver] Ez a csomag rossz meretu FOS!";
      break;
    }

    if (UpdateFrame(data.get(), frame_) != 0) {
      qWarning() << "[MUEBReceiver] Ez a csomag invalid FOS!";
      break;
    }

    emit frameChanged(frame_);
  }
}
