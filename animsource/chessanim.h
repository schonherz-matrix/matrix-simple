#ifndef CHESS_ANIM_H_INCLUDED
#define CHESS_ANIM_H_INCLUDED

#include "animsender.h"
#include "frame.h"
#include "color.h"
#include <QColor>

class ChessAnim: public AnimInterface {
	private:
		Color primary_color_, secondary_color_;
		int fl_;
		int cntr_;
		bool first_;
		Frame f1_, f2_;
	public:
		ChessAnim(const QColor& primary_color, const QColor& secondary_color, int num);
		Frame nextFrame() override;
};

#endif
