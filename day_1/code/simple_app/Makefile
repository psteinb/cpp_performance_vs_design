all : simple_app simple_app.s simple_app.disassembled

simple_app : simple_app.cpp
	$(CXX) -g $< -o $@ 

simple_app.s : simple_app.cpp
	$(CXX) -g -S $< -o $@ 

simple_app.disassembled : simple_app
	objdump -d $< | c++filt > $@ 2>&1 &
