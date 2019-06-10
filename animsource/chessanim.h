#ifndef CHESS_ANIM_H_INCLUDED
#define CHESS_ANIM_H_INCLUDED

#include <QColor>
#include "animsender.h"

class ChessAnim : public AnimInterface {
 private:
  QColor primary_color_, secondary_color_;
  int fl_;
  int cntr_;
  bool first_;
  QImage f1_, f2_;

 public:
  ChessAnim(const QColor& primary_color, const QColor& secondary_color,
            int num);
  QImage nextFrame() override;
};

#endif
