all:
	$(CXX) -std=c++11 -O3 nsa.cpp -o nsa -lpthread

debug:
	$(CXX) -std=c++11 -O0 -g -Wall nsa.cpp 0o nsa -lpthread
