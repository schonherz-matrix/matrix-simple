#ifndef DRAW_SENDER_H_INCLUDED
#define DRAW_SENDER_H_INCLUDED

#include "timer.h"
#include "frame.h"
#include "color.h"
#include "muebtransmitter.h"
#include <string>
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>


class DrawSender: public QObject {
	Q_OBJECT
	private:
		QColor color_;
		Frame frame_;
		std::mutex m_;
		std::unique_ptr<Timer> timer_;
        
        MUEBTransmitter transmitter_;
		void packetCallback();
	public:
		DrawSender();
		virtual ~DrawSender();
	public slots:
		void setColor(const QColor& color);
		void changeCell(const QPoint& cell);
		void fillFrame();
	signals:
		void frameChanged(Frame frame);
};

#endif
