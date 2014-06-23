SRCFILES=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCFILES))

ifeq ($(CXX),g++)
CXXFLAGS=-O2 -march=native -std=c++11
endif

ifeq ($(CXX),clang++)
CXXFLAGS+=-O2 -march=native -std=c++11
endif

ifeq ($(CXX),icpc)
CXXFLAGS+=-O2 -xHost -std=c++11
endif

all : $(TARGETS)

$(TARGETS) : % : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	rm -vf $(TARGETS) 
