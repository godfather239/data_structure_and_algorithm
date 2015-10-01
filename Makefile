all: binary_tree sort linklist string_operation

binary_tree : binary_tree.cpp
	g++ -o $@ $<
sort : sort.cpp
	g++ -o $@ $<
linklist : linklist.cpp
	g++ -o $@ $<
string_operation : string_operation.cpp
	g++ -o $@ $<

clean:
	rm -f test main.o
