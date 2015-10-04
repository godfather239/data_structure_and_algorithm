CXX = g++
CXXFLAGS = -g

OUTPUT = binary_tree sort bit_operation search
all: $(OUTPUT)

SRC := $(wildcard *.cpp)
OBJS := $(SRC:.CPP=.o)

binary_tree : binary_tree.o
	$(CXX) -o $@ $< $(CXXFLAGS)
sort : sort.o
	$(CXX) -o $@ $< $(CXXFLAGS)
bit_operation : bit_operation.o
	$(CXX) -o $@ $< $(CXXFLAGS)
search : search.o
	$(CXX) -o $@ $< $(CXXFLAGS)

#sort : sort.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)
#linklist : linklist.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)
#string_operation : string_operation.cpp
#	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OUTPUT) *.o
