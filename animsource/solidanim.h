#ifndef SOLID_ANIM_H_INCLUDED
#define SOLID_ANIM_H_INCLUDED

#include "animsender.h"
#include "frame.h"
#include "color.h"
#include <QColor>

class SolidAnim: public AnimInterface {
	private:
		Color primary_color_, secondary_color_;
		int fl_;
		int cntr_;
		bool first_;
		Frame f1_, f2_;
	public:
		SolidAnim(const QColor& primary_color, const QColor& secondary_color, int num);
		Frame nextFrame() override;
};

#endif

