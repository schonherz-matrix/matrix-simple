#include "verticalanim.h"

#include "array2D.hpp"

VerticalAnim::VerticalAnim(const QColor& primary_color, const QColor& secondary_color, int num, bool is_vertical):
    primary_color_{Color{primary_color.red(), primary_color.green(), primary_color.blue()}},
    secondary_color_{Color{secondary_color.red(), secondary_color.green(), secondary_color.blue()}},
    num_{num}
{
    is_vertical_ = is_vertical;
    height = 26;
    width = 32;
    frame_.pixels = Array2D<Color>{width, height};
    i_ = 0;
}

Frame VerticalAnim::nextFrame() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int r = 0;
            int g = 0;

            if(is_vertical_){
                if(((i_+x*10)%512) > 255){
                    r = 255-((i_+x*10)%256);
                } else{
                    r = (i_+x*10)%256;
                }

                if((((i_+256)+x*10)%512) > 255){
                    g = 255-((i_+x*10)%256);
                } else{
                    g = (i_+x*10)%256;
                }
            } else{
                if(((i_+y*10)%512) > 255){
                    r = 255-((i_+y*10)%256);
                } else{
                    r = (i_+y*10)%256;
                }

                if((((i_+256)+y*10)%512) > 255){
                    g = 255-((i_+y*10)%256);
                } else{
                    g = (i_+y*10)%256;
                }
            }

            double first_percent = (double) r/255;
            double second_percent = (double) g/255;

            frame_.pixels(x,y) = Color{
                    primary_color_.r*first_percent+secondary_color_.r*second_percent,
                    primary_color_.g*first_percent+secondary_color_.g*second_percent,
                    primary_color_.b*first_percent+secondary_color_.b*second_percent};
        }
    }

    i_ += num_;
    return frame_;
}

