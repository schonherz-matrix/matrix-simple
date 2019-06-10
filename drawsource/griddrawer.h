#ifndef GRID_DRAWER_H_INCLUDED
#define GRID_DRAWER_H_INCLUDED

#include <QBrush>
#include <QImage>
#include <QMouseEvent>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class GridDrawer : public QWidget {
  Q_OBJECT

 protected:
  void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 public:
  GridDrawer(QWidget* parent = nullptr, int x = 10, int y = 0,
             int windowSize = 10);
  QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  QSize sizeHint() const Q_DECL_OVERRIDE;
 public slots:
  void setFrame(QImage frame);
 signals:
  void clickEvent(const QPoint&);

 private:
  QImage frame_;
  int x_, y_;
  int windowSize_;
  QPoint screenToGrid(const QPoint&);
};

#endif
