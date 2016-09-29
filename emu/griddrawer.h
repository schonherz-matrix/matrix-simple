#ifndef GRID_DRAWER_H_INCLUDED
#define GRID_DRAWER_H_INCLUDED

#include "frame.h"
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class GridDrawer: public QWidget {
	Q_OBJECT
	private:
		Frame frame_;
		int x_, y_;
		int windowSize_;
	protected:
		void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
	public:
		GridDrawer(QWidget* parent = 0, int x = 10, int y = 0, int windowSize = 10);
		QSize minimumSizeHint() const Q_DECL_OVERRIDE;
		QSize sizeHint() const Q_DECL_OVERRIDE;
	public slots:
		void setFrame(Frame frame);
};

#endif
