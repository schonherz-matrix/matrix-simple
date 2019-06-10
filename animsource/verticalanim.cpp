#include "verticalanim.h"

VerticalAnim::VerticalAnim(const QColor& primary_color,
                           const QColor& secondary_color, int num,
                           bool is_vertical)
    : primary_color_{primary_color},
      secondary_color_{secondary_color},
      num_{num},
      frame_(32, 26, QImage::Format_RGB888) {
  is_vertical_ = is_vertical;
  height = 26;
  width = 32;
  i_ = 0;
}

QImage VerticalAnim::nextFrame() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int r = 0;
      int g = 0;

      if (is_vertical_) {
        if (((i_ + x * 10) % 512) > 255) {
          r = 255 - ((i_ + x * 10) % 256);
        } else {
          r = (i_ + x * 10) % 256;
        }

        if ((((i_ + 256) + x * 10) % 512) > 255) {
          g = 255 - ((i_ + x * 10) % 256);
        } else {
          g = (i_ + x * 10) % 256;
        }
      } else {
        if (((i_ + y * 10) % 512) > 255) {
          r = 255 - ((i_ + y * 10) % 256);
        } else {
          r = (i_ + y * 10) % 256;
        }

        if ((((i_ + 256) + y * 10) % 512) > 255) {
          g = 255 - ((i_ + y * 10) % 256);
        } else {
          g = (i_ + y * 10) % 256;
        }
      }

      double first_percent = (double)r / 255;
      double second_percent = (double)g / 255;

      frame_.setPixelColor(
          x, y,
          QColor(primary_color_.red() * first_percent +
                     secondary_color_.red() * second_percent,
                 primary_color_.green() * first_percent +
                     secondary_color_.green() * second_percent,
                 primary_color_.blue() * first_percent +
                     secondary_color_.blue() * second_percent));
    }
  }

  i_ += num_;
  return frame_;
}
