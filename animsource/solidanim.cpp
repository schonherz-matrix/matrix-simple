#include "solidanim.h"

SolidAnim::SolidAnim(const QColor& primary_color, const QColor& secondary_color,
                     int num)
    : primary_color_(primary_color),
      secondary_color_(secondary_color),
      fl_{num},
      cntr_{0},
      first_{true},
      f1_(32, 26, QImage::Format_RGB888),
      f2_(32, 26, QImage::Format_RGB888) {
  f1_.fill(primary_color);
  f2_.fill(secondary_color);
}

QImage SolidAnim::nextFrame() {
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
