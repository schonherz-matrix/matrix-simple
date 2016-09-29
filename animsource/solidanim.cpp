#include "solidanim.h"
#include "array2D.hpp"

SolidAnim::SolidAnim(const QColor& primary_color, const QColor& secondary_color, int num):
	primary_color_{Color{primary_color.red(), primary_color.green(), primary_color.blue()}},
	secondary_color_{Color{secondary_color.red(), secondary_color.green(), secondary_color.blue()}},
	fl_{num},
	cntr_{0},
	first_{true}
{
	f1_.pixels = Array2D<Color>{32, 26};
	f2_.pixels = Array2D<Color>{32, 26};
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 26; y++) {
			f1_.pixels(x,y) = primary_color_;
			f2_.pixels(x,y) = secondary_color_;
		}
	}
}

Frame SolidAnim::nextFrame() {
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

