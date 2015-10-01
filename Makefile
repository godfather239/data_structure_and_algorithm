CXX = g++
CXXFLAGS = -g

OUTPUT = binary_tree
all: $(OUTPUT)

SRC := $(wildcard *.cpp)
OBJS := $(SRC:.CPP=.O)

binary_tree : binary_tree.o
	$(CXX) -o $@ $< $(CXXFLAGS)
#sort : sort.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)
#linklist : linklist.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)
#string_operation : string_operation.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OUTPUT) *.o
