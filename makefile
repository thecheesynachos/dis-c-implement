CXX = g++
CXXFLAGS = -Wall -g

main: main.cpp disc.h mtree.h util.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

.PHONY: clean

clean:
	rm -f ./*.o main