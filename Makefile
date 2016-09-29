CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread
QMAKE = /usr/lib64/qt5/bin/qmake

.PHONY: all clean

all: emu/Emu colorsource/ColorSource animsource/AnimSource matrixsource/MatrixSource

clean:
	$(MAKE) clean -C mueb
	$(MAKE) clean -C emu
	$(MAKE) clean -C colorsource
	$(MAKE) clean -C animsource
	$(MAKE) clean -C matrixsource

mueb/libMUEB.a:
	$(MAKE) -C mueb

emu/Emu: mueb/libMUEB.a
	$(MAKE) -C emu

colorsource/ColorSource: mueb/libMUEB.a
	$(MAKE) -C colorsource

animsource/AnimSource: mueb/libMUEB.a
	$(MAKE) -C animsource

matrixsource/MatrixSource: mueb/libMUEB.a
	$(MAKE) -C matrixsource

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
