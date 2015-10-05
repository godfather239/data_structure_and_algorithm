CXX = g++
CXXFLAGS = -g

OUTPUT = binary_tree sort bit_operation search sub_array_sum
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
sub_array_sum : sub_array_sum.o
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OUTPUT) *.o
