#ifndef ANIM_FACTORY_H_INCLUDED
#define ANIM_FACTORY_H_INCLUDED

#include "animsender.h"
#include <map>
#include <string>
#include <QColor>

class AnimFactory {
	public:
		enum AnimType {
            CHESS,
            VERTICAL,
            HORIZONTAL,
            SOLID
		};
		const static std::map<std::string, AnimFactory::AnimType> AnimTypeString;
		static AnimInterface* getAnim(AnimType type, const QColor& primary_color, const QColor& secondary_color, int num);
};

#endif
