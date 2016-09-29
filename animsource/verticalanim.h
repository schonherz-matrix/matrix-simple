#ifndef VERTICALANIM_H
#define VERTICALANIM_H


#include "animsender.h"
#include "frame.h"
#include "color.h"
#include <QColor>

class VerticalAnim: public AnimInterface {
    private:
        Color primary_color_, secondary_color_;
        int num_;
        int height;
        int width;
        int i_;
        bool is_vertical_;
        Frame frame_;
    public:
        VerticalAnim(const QColor& primary_color, const QColor& secondary_color, int num, bool is_vertical);
        Frame nextFrame() override;
};

#endif // VERTICALANIM_H
