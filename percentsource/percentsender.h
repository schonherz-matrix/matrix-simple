#ifndef PERCENT_SENDER_H_INCLUDED
#define PERCENT_SENDER_H_INCLUDED

#include "timer.h"
#include "frame.h"
#include "color.h"
#include "muebtransmitter.h"
#include <string>
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>

class PercentSender: public QObject {
	Q_OBJECT
	private:
        Frame frame_;
        int percent_;
        int flashCount_;
        std::unique_ptr<Timer> flashTimer_;
        
		std::unique_ptr<Timer> timer_;
		std::mutex m_;
        
        MUEBTransmitter transmitter_;
		void packetCallback();
        void flashCallback();
	public:
		PercentSender();
		virtual ~PercentSender();
	public slots:
		void setPercent(int percent);
};

#endif
