sorting: sorting.cpp sorting.hpp
	g++ -c sorting.cpp

mytests: mytests.o sorting.o sorting
	g++ -c mytests.cpp
	g++ -o mytests mytests.o sorting.o
	./mytests

clean:
	rm -f *.o sorting mytests