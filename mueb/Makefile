CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -lm -lpthread

.PHONY: all clean

all: libMUEB.a

clean:
	rm -f *.o libMUEB.a ../common/*.o

libMUEB.a: muebtransmitter.o muebreceiver.o udpsocket.o udpsocket_linux.o ../common/serialization.o
	ar rcs $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
