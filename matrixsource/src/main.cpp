#include <iostream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <thread>

#include "MatrixVideoPlayer.h"
#include "Q4XLoader.h"

#include "MatrixPlayerWindow.h"
#include <QtWidgets/QApplication>

using namespace std;
using namespace std::chrono;


int test() {
	MatrixVideoPlayer player;
	player.debugLoad(1000); // 33ms*1000 = 33s
	player.debugSetFrameTime(0.050);
	player.play();

	this_thread::sleep_for(milliseconds(1000));
	player.setTime(milliseconds(15077));
	this_thread::sleep_for(milliseconds(1000));
	player.pause();
	this_thread::sleep_for(milliseconds(1000));
	player.stop();
	player.clear();

    return 0;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MatrixPlayerWindow w;
    w.show();
    
    //Q4XLoader loader;
    //loader.load("/home/petiaccja/Programming/SchMatrix/01-softbambi.q4x");
    

    return a.exec();
}
