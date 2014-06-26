SRCFILES=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCFILES))

all : $(TARGETS)

$(TARGETS) : % : %.cpp
	$(CXX) $(CXXFLAGS) -fopenmp $< -o $@

clean :
	rm -vf $(TARGETS)
