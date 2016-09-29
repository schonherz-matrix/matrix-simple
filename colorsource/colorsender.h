#ifndef COLOR_SENDER_H_INCLUDED
#define COLOR_SENDER_H_INCLUDED

#include "timer.h"
#include "frame.h"
#include "color.h"
#include "muebtransmitter.h"
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>


class ColorSender: public QObject {
	Q_OBJECT
	
	private:
		QColor color_;
		std::mutex m_;
		std::unique_ptr<Timer> timer_;
        
        MUEBTransmitter transmitter;
		void packetCallback();
	public slots:
		void setColor(const QColor& color);
	public:
		ColorSender();
		virtual ~ColorSender();
};

#endif
