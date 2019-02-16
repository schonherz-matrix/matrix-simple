CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread

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
	rm -f emu/Emu colorsource/ColorSource animsource/AnimSource drawsource/DrawSource matrixsource/MatrixSource windowtestsource/WindowTestSource percentsource/PercentSource

mueb/libMUEB.a:
	$(MAKE) -C mueb

emu/Emu: mueb/libMUEB.a
	qmake emu/ -o emu/Makefile
	$(MAKE) -C emu

colorsource/ColorSource: mueb/libMUEB.a
	qmake colorsource/ -o colorsource/Makefile
	$(MAKE) -C colorsource

animsource/AnimSource: mueb/libMUEB.a
	qmake animsource/ -o animsource/Makefile
	$(MAKE) -C animsource

drawsource/DrawSource: mueb/libMUEB.a
	qmake drawsource/ -o drawsource/Makefile
	$(MAKE) -C drawsource

matrixsource/MatrixSource: mueb/libMUEB.a
	qmake matrixsource/ -o matrixsource/Makefile
	$(MAKE) -C matrixsource

windowtestsource/WindowTestSource: mueb/libMUEB.a
	qmake windowtestsource/ -o windowtestsource/Makefile
	$(MAKE) -C windowtestsource

percentsource/PercentSource: mueb/libMUEB.a
	qmake percentsource/ -o percentsource/Makefile
	$(MAKE) -C percentsource

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
