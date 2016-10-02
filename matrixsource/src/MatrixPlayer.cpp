
#include "MatrixPlayer.h"
#include "Q4XLoader.h"

#include <exception>
#include <iostream>
#include <chrono>
#include <cmath>


using namespace std;
using namespace std::chrono;


MatrixPlayer::MatrixPlayer() : videoListener(*this), audioListener(*this) {
    audioEndedFlag = videoEndedFlag = false;
    videoPlayer.addListener(&videoListener);
    audioPlayer.addListener(&audioListener);
    
           
        // set presentation method
        videoPlayer.PresentFrame = [this](const PlayerFrame& frame) {
            Frame sf;
            sf.pixels.resize(frame.width(), frame.height());
            for (size_t x = 0; x<frame.width(); x++) {
                for (size_t y = 0; y<frame.height(); y++) {
                    sf.pixels(x,y) = frame(x,y);
                }            
            }
            sf.id = 0;
            transmitter.sendFrame(sf);
        };
}

MatrixPlayer::~MatrixPlayer() {
    stopSynchronizer();
}


// --- Playback control --- //
void MatrixPlayer::play() {
    if (videoEndedFlag || audioEndedFlag) {
        videoPlayer.stop();
        audioPlayer.stop();
    }
    
    videoPlayer.play();
    audioPlayer.play();
    
    startSynchronizer();
}

void MatrixPlayer::pause() {
    stopSynchronizer();
    videoPlayer.pause();
    audioPlayer.pause();
}

void MatrixPlayer::stop() {
    stopSynchronizer();
    audioEndedFlag = videoEndedFlag = false;
    videoPlayer.stop();
    audioPlayer.stop();
}

void MatrixPlayer::setVolume(float volume) {
    lock_guard<mutex> lk(subPlayerMutex);
    audioPlayer.setVolume(volume);
}

float MatrixPlayer::getVolume() const {
    lock_guard<mutex> lk(subPlayerMutex);
    return audioPlayer.getVolume();
}

// --- Get state --- //
MatrixPlayer::eState MatrixPlayer::getState() const {
    lock_guard<mutex> lk(subPlayerMutex);
    return (eState)videoPlayer.getState();
}

std::chrono::microseconds MatrixPlayer::getTime() const {
    lock_guard<mutex> lk(subPlayerMutex);
    return videoPlayer.getTime();
}

std::chrono::microseconds MatrixPlayer::getDuration() const {
    lock_guard<mutex> lk(subPlayerMutex);
    return videoPlayer.getDuration();
}

// --- Input data --- //
bool MatrixPlayer::load(const std::string& filePath) {
    clear();
    
    Q4XLoader loader;
    bool isLoaded = loader.load(filePath);
    bool isVideoOk = false;
    bool isAudioOk = true;
    
    if (!isLoaded) {
        return false;
    }
        
    if (isLoaded) {
        loader.resample(microseconds(1000*1000/30));
        isVideoOk = videoPlayer.load(loader.getFrames().data(), loader.getFrames().size(), loader.getFrameTime());
        if (loader.getSoundData()) {
            hasAudio = true;
            isAudioOk = audioPlayer.load(loader.getSoundData(), loader.getSoundDataSize());
        }
        else {
            hasAudio = false;
        }
    }
    
    if (isAudioOk && isVideoOk) {
        return true;
    }
    else {
        clear();
        return false;
    }
}


void MatrixPlayer::clear() {
    stopSynchronizer();
    videoPlayer.clear();
    audioPlayer.clear();
    audioEndedFlag = videoEndedFlag = false;
}


void MatrixPlayer::addListener(MatrixPlayerListener* listener) {
    listeners.insert(listener);
}

void MatrixPlayer::removeListener(MatrixPlayerListener* listener) {
    listeners.erase(listener);
}


void MatrixPlayer::notifyListenersState(eState state) {
    for (auto listener : listeners) {
        listener->onStateChanged(state);
    }
}

void MatrixPlayer::notifyListenersTime(double time) {
    for (auto listener : listeners) {
        listener->onTimeChanged(time);
    }    
}

void MatrixPlayer::notifyListenersTrackEnd() {
    for (auto listener : listeners) {
        listener->onTrackEnded();
    }    
}

void MatrixPlayer::notifyListenersFrame(const PlayerFrame& frame) {
    for (auto listener : listeners) {
        listener->onFrameChanged(frame);
    }
}


void MatrixPlayer::startSynchronizer() {
    stopSynchronizer();
    runSynchronizer = true;
    synchronizerThread = thread([this]{
        unsigned long long counter = 0;
        while (runSynchronizer) {
            if (counter%20 == 0) {
                if (hasAudio) {
                    lock_guard<mutex> lk(subPlayerMutex);
                    auto time = audioPlayer.getTime();
                    videoPlayer.syncToExternalSource(time);
                }
            }
            counter++;
            this_thread::sleep_for(milliseconds(50));
        }
    });
}

void MatrixPlayer::stopSynchronizer() {
    runSynchronizer = false;
    if (synchronizerThread.joinable()) {
        synchronizerThread.join();
    }
}




void MatrixPlayer::VideoListener::onStateChanged(MatrixVideoPlayer::eState state) {
    parent.notifyListenersState((eState)state);
}

void MatrixPlayer::VideoListener::onTimeChanged(double time) {
    parent.notifyListenersTime(time);
}


void MatrixPlayer::VideoListener::onFrameChanged(const PlayerFrame& frame) {
    parent.notifyListenersFrame(frame);
}

void MatrixPlayer::VideoListener::onTrackEnded() {
    parent.runSynchronizer = false;
    if (parent.audioEndedFlag || !parent.hasAudio) {
        parent.notifyListenersTrackEnd();
        parent.audioEndedFlag = parent.videoEndedFlag = false;
    }
    else {
        parent.videoEndedFlag = true;
    }
}




void MatrixPlayer::AudioListener::onStateChanged(MatrixAudioPlayer::eState) {
    
}

void MatrixPlayer::AudioListener::onTrackEnded() {
    parent.runSynchronizer = false;
    if (parent.videoEndedFlag) {
        parent.notifyListenersTrackEnd();
        parent.audioEndedFlag = parent.videoEndedFlag = false;
    }
    else {
        parent.audioEndedFlag = true;
    }
}
















