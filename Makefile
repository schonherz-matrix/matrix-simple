CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread
QMAKE = /usr/lib64/qt5/bin/qmake

.PHONY: all clean

all: testsource testemu emu/Emu colorsource/ColorSource

clean:
	rm -f *.o testsource testemu
	$(MAKE) clean -C mueb
	$(MAKE) clean -C emu
	$(MAKE) clean -C colorsource

mueb/libMUEB.a:
	$(MAKE) -C mueb

testsource: testsource.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

testemu: testemu.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

emu/Emu:
	$(MAKE) -C emu

colorsource/ColorSource:
	$(MAKE) -C colorsource

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
