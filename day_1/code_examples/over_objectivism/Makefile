CXX ?= g++
CXXFLAGS ?= -O2 -std=c++11 -march=native -ffast-math

all : l2norm l1norm

l2norm : l2norm.cpp
	$(CXX) $(CXXFLAGS)  $< -o $@

l1norm : l1norm.cpp
	$(CXX) $(CXXFLAGS)  $< -o $@
