#include "chessanim.h"

ChessAnim::ChessAnim(const QColor& primary_color, const QColor& secondary_color,
                     int num)
    : primary_color_(primary_color),
      secondary_color_(secondary_color),
      fl_{num},
      cntr_{0},
      first_{true},
      f1_(32, 26, QImage::Format_RGB888),
      f2_(32, 26, QImage::Format_RGB888)

{
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 26; y++) {
      f1_.setPixelColor(
          x, y, ((x / 2 + y / 2) % 2) ? primary_color_ : secondary_color_);
      f2_.setPixelColor(
          x, y, ((x / 2 + y / 2) % 2) ? secondary_color_ : primary_color_);
    }
  }
}

QImage ChessAnim::nextFrame() {
  if (cntr_ == fl_) {
    if (first_) {
      first_ = false;
    } else {
      first_ = true;
    }
    cntr_ = 0;
  } else {
    cntr_++;
  }
  if (first_) {
    return f1_;
  } else {
    return f2_;
  }
}
