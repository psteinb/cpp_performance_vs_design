CXX ?= g++
CXXFLAGS ?= -O2 -std=c++11

all : virtual_inheritance print_class_layout

virtual_inheritance :
	$(CXX) $(CXXFLAGS) virtual_inheritance.cpp   -o virtual_inheritance

print_class_layout :
	clang -cc1 -fdump-record-layouts print_class_layout.cpp
