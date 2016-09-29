CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread

.PHONY: all clean

all: testsource testemu

clean:
	rm -f *.o testsource testemu
	$(MAKE) clean -C mueb

mueb/libMUEB.a:
	$(MAKE) -C mueb

testsource: testsource.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

testemu: testemu.o mueb/libMUEB.a
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
