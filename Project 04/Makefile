all: mytests

mytests: mytests.o graph.o
	g++ -std=c++14 -o mytests mytests.o graph.o
	./mytests < myGraph.txt

mytests.o: mytests.cpp Graph.hpp
	g++ -std=c++14 -o mytests.o -c mytests.cpp

graph.o: Graph.hpp Graph.cpp customexceptions.hpp
	g++ -std=c++14 -o graph.o -c Graph.cpp

clean:
	rm -f *.o mytests
	clear
