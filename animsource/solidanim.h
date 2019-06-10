#ifndef SOLID_ANIM_H_INCLUDED
#define SOLID_ANIM_H_INCLUDED

#include <QColor>
#include "animsender.h"

class SolidAnim : public AnimInterface {
 private:
  QColor primary_color_, secondary_color_;
  int fl_;
  int cntr_;
  bool first_;
  QImage f1_, f2_;

 public:
  SolidAnim(const QColor& primary_color, const QColor& secondary_color,
            int num);
  QImage nextFrame() override;
};

#endif
