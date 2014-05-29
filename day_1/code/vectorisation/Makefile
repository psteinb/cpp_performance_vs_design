SRCFILES=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCFILES))
S_TARGETS=$(patsubst %.cpp,%.s,$(SRCFILES))

ifeq ($(CXX),g++)
CXXFLAGS=-O2 -march=native -ftree-vectorize -ftree-vectorizer-verbose=2
endif

ifeq ($(CXX),clang++)
CXXFLAGS+=-O2 -march=native -fvectorize
endif

ifeq ($(CXX),icpc)
CXXFLAGS+=-O2 -xHost -vec -vec-report=2
endif

all : $(TARGETS)

$(TARGETS) : % : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

MatrixSum.s : MatrixSum.cpp
	$(CXX) $(CXXFLAGS) -S $< -o $@

clean :
	rm -vf $(TARGETS) $(S_TARGETS) 
