CXX      = clang++ -g -std=c++17
CXXFLAGS = -Wall -Wextra -pedantic
LIBS     = 
TARGETS  = show-rep show-types

all: $(TARGETS)


show-types: show-types.o
	$(CXX) -o $@ $^ $(LIBS)

show-rep: show-rep.o
	$(CXX) -o $@ $^ $(LIBS)

show-rep.o: show-rep.cpp show-rep-internals.hpp
show-types.o: show-types.cpp show-types-internals.hpp

clean:
	rm -f *.o $(TARGETS)
