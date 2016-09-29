#include "griddrawer.h"
#include "color.h"
#include <QPainter>

GridDrawer::GridDrawer(QWidget* parent, int x, int y, int windowSize): QWidget{parent}, x_{x}, y_{y}, windowSize_{windowSize} {
	frame_.pixels = Array2D<Color>{x_, y_};
	for (int x = 0; x < frame_.pixels.getWidth(); x++) {
		for (int y = 0; y < frame_.pixels.getHeight(); y++) {
			frame_.pixels(x,y) = Color{0, 0, 0};
		}
	}
}

QSize GridDrawer::minimumSizeHint() const {
    return QSize{x_*windowSize_, y_*windowSize_};
}

QSize GridDrawer::sizeHint() const {
    return QSize{x_*windowSize_, y_*windowSize_};
}

void GridDrawer::setFrame(Frame frame) {
	frame_ = frame;
	update();
}

void GridDrawer::paintEvent(QPaintEvent* event) {
	QPainter painter{this};
	for (int x = 0; x < frame_.pixels.getWidth(); x++) {
		for (int y = 0; y < frame_.pixels.getHeight(); y++) {
			painter.setBrush(QBrush{QColor{frame_.pixels(x,y).r, frame_.pixels(x,y).g, frame_.pixels(x,y).b}});
			painter.drawRect(windowSize_*x, windowSize_*y, windowSize_, windowSize_);
		}
	}
}
