BINARY = source
OBJECTS = main.o timer.o testsource.o rpc.o
HEADERS = src/timer.h src/testsource.h src/rpc.h src/matrix.h src/rgb.h

CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -g -lpthread

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

