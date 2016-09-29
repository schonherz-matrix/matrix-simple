#ifndef FRAME_PROCESSOR_H_INCLUDED
#define FRAME_PROCESSOR_H_INCLUDED

#include "color.h"
#include "muebreceiver.h"
#include <string>
#include <mutex>
#include <memory>
#include <deque>
#include <QObject>

class FrameProcessor: public QObject {
	Q_OBJECT
	private:
		std::mutex m_;
		MUEBReceiver receiver_;
        void receiverCallback(Frame f);
	signals:
		void newFrame(Frame frame);
	public:
		FrameProcessor();
		virtual ~FrameProcessor();
};

#endif
