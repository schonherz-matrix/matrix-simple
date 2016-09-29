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

class AnimInterface {
	public:
		virtual Frame nextFrame() = 0;
		virtual ~AnimInterface();
};

class AnimSender: public QObject {
	Q_OBJECT
	private:
		std::unique_ptr<AnimInterface> anim_;
		std::unique_ptr<Timer> timer_;
		std::mutex m_;
        
        MUEBTransmitter transmitter_;
		void packetCallback();
	public:
		AnimSender();
		virtual ~AnimSender();
	public slots:
		void setAnim(AnimInterface* anim);
};

#endif
