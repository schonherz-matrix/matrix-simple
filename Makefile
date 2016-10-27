CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread
QMAKE = /usr/lib64/qt5/bin/qmake

.PHONY: all clean

all: emu/Emu colorsource/ColorSource animsource/AnimSource drawsource/DrawSource matrixsource/MatrixSource windowtestsource/WindowTestSource percentsource/PercentSource

clean:
	$(MAKE) clean -C mueb
	$(MAKE) clean -C emu
	$(MAKE) clean -C colorsource
	$(MAKE) clean -C animsource
	$(MAKE) clean -C drawsource
	$(MAKE) clean -C matrixsource
	$(MAKE) clean -C windowtestsource
	$(MAKE) clean -C percentsource
	rm -f emu/Emu colorsource/ColorSource animsource/AnimSource drawsource/DrawSource matrixsource/MatrixSource windowtestsource/WindowTestSource

mueb/libMUEB.a:
	$(MAKE) -C mueb

emu/Emu: mueb/libMUEB.a
	$(MAKE) -C emu

colorsource/ColorSource: mueb/libMUEB.a
	$(MAKE) -C colorsource

animsource/AnimSource: mueb/libMUEB.a
	$(MAKE) -C animsource

drawsource/DrawSource: mueb/libMUEB.a
	$(MAKE) -C drawsource

matrixsource/MatrixSource: mueb/libMUEB.a
	$(MAKE) -C matrixsource

windowtestsource/WindowTestSource: mueb/libMUEB.a
	$(MAKE) -C windowtestsource

percentsource/PercentSource: mueb/libMUEB.a
	$(MAKE) -C percentsource

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
