CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra -std=c++11

all: thrower

thrower: thrower.o throw_exception.o
	$(CC) $(CXXFLAGS) -o $@ $^

thrower.o: thrower.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

throw_exception.o: throw_exception.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o thrower
