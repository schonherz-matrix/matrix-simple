#include "muebtransmitter.h"

MUEBTransmitter::MUEBTransmitter(QObject *parent, QString addr, uint16_t port)
    : QObject(parent), socket_(this), address_(addr), port_(port) {
  qInfo() << "UDP Socket will send frame to " << address_.toString();
}

// PN = package number
// wn = window number
inline static void CreatePackage(Frame f, uint8_t PN, uint8_t out[]) {
  out[0] = 0x01;
  out[1] = PN + 1;  // 1, 2, 3, 4 

  // PN * 52: wn = 0, 52, 104, 156
  // (PN + 1)*52: wn = 52, 104, 156, 208
  // (PN + 1)*52
  for (uint8_t wn = PN * 52, i = 0; wn < (PN + 1) * 52; ++wn, ++i) {
    // wn = 0, i = 0

    Color bf, jf, bl, jl;  // one side

    // read frame
    //                  x                   y
    bf = f.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 0);
    jf = f.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 0);
    bl = f.pixels((wn % 16) * 2 + 0, (wn / 16) * 2 + 1);
    jl = f.pixels((wn % 16) * 2 + 1, (wn / 16) * 2 + 1);

    // start from the 2 index see out[0], out[1]
    // 6 item one window
    // 0-5 offset from the start of the window
    out[i * 6 + 0 + 2] = ((bf.r >> 1) & 0x70) | (bf.g >> 5);
    out[i * 6 + 1 + 2] = ((bf.b >> 1) & 0x70) | (jf.r >> 5);
    out[i * 6 + 2 + 2] = ((jf.g >> 1) & 0x70) | (jf.b >> 5);

    out[i * 6 + 3 + 2] = ((bl.r >> 1) & 0x70) | (bl.g >> 5);
    out[i * 6 + 4 + 2] = ((bl.b >> 1) & 0x70) | (jl.r >> 5);
    out[i * 6 + 5 + 2] = ((jl.g >> 1) & 0x70) | (jl.b >> 5);
  }
}

void MUEBTransmitter::sendFrame(Frame frame) {
  if (frame.pixels.getHeight() != 26 || frame.pixels.getWidth() != 32) {
    qWarning() << "[MUEBTransmitter] Ez a csomag FOS!";
    return;
  }

  std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(314);

  for (uint8_t i = 0; i < 4; i += 1) {
    CreatePackage(frame, i, data.get());

    socket_.writeDatagram(reinterpret_cast<char *>(data.get()), 314, address_,
                          10000);
  }
}
