#include "frameprocessor.h"
#include <functional>
#include <thread>
#include <cmath>
#include <QDebug>

FrameProcessor::FrameProcessor()
    : receiver_{std::bind(&FrameProcessor::receiverCallback, this, std::placeholders::_1)}
{
}

void FrameProcessor::receiverCallback(Frame f) {
    std::lock_guard<std::mutex> lock{m_};
    emit newFrame(f);
}

FrameProcessor::~FrameProcessor() {
	receiver_.stop();
}
