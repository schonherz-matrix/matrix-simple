#ifndef VERTICALANIM_H
#define VERTICALANIM_H

#include <QColor>
#include "animsender.h"

class VerticalAnim : public AnimInterface {
 private:
  QColor primary_color_, secondary_color_;
  int num_;
  int height;
  int width;
  int i_;
  bool is_vertical_;
  QImage frame_;

 public:
  VerticalAnim(const QColor& primary_color, const QColor& secondary_color,
               int num, bool is_vertical);
  QImage nextFrame() override;
};

#endif  // VERTICALANIM_H
