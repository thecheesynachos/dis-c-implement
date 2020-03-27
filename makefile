CXX = g++
CXXFLAGS = -Wall -g -std=c++14

all: disc_bulkinsert_run disc_singleinsert_run disc_parallel_run

disc_bulkinsert_run: disc_bulkinsert/main.cpp disc_bulkinsert/disc.h disc_bulkinsert/mtree.h disc_bulkinsert/util.cpp
	$(CXX) $(CXXFLAGS) -o disc_bulkinsert_run disc_bulkinsert/main.cpp

disc_singleinsert_run: disc_singleinsert/main.cpp disc_singleinsert/disc.h disc_singleinsert/mtree.h disc_singleinsert/util.cpp
	$(CXX) $(CXXFLAGS) -o disc_singleinsert_run disc_singleinsert/main.cpp

disc_parallel_run: disc_parallel/main.cpp disc_parallel/disc.h disc_parallel/mtree.h disc_parallel/util.cpp
	$(CXX) $(CXXFLAGS) -fcilkplus -o disc_parallel_run disc_parallel/main.cpp

.PHONY: clean

clean:
	rm -rf ./disc_*_run
