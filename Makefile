CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread

.PHONY: all clean

all: source emu

clean:
	rm -f *.o main
	$(MAKE) clean -C mueb

mueb/libMUEB.a:
	$(MAKE) -C mueb

source: source.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

emu: emu.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
