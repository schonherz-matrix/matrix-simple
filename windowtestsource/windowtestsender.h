#ifndef WINDOW_TEST_SENDER_H_INCLUDED
#define WINDOW_TEST_SENDER_H_INCLUDED

#include "timer.h"
#include "frame.h"
#include "color.h"
#include "muebtransmitter.h"
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>


class WindowTestSender: public QObject {
	Q_OBJECT
	
	private:
		int speed_;
        int countdown_;
        int color_;
        int window_;
		std::mutex m_;
		std::unique_ptr<Timer> timer_;
        
        MUEBTransmitter transmitter_;
		void packetCallback();
	public slots:
		void setSpeed(int speed);
	public:
		WindowTestSender();
		virtual ~WindowTestSender();
};

#endif
