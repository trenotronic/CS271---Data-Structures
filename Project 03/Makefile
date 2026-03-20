all: mytests

mytests: mytests.o 
	g++ -o mytests mytests.o 
	./mytests

mytests.o: mytests.cpp HashMap.cpp HashMap.hpp HashMapTree.cpp HashMapTree.hpp Set.cpp Set.hpp
	g++ -o mytests.o -c mytests.cpp

HashMap.o: HashMap.cpp HashMap.hpp
	g++ -c HashMap.cpp

HashMapTree.o: HashMapTree.cpp HashMapTree.hpp
	g++ -c HashMapTree.cpp

Set.o: Set.cpp Set.hpp
	g++ -c Set.cpp

performance.o: performance.cpp
	g++ -c performance.cpp

performance: performance.o
	g++ -o performance performance.o
	./performance

checkleaks:
	g++ -o mytests mytests.o
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  ./mytests

clean:
	rm *.o mytests performance
	clear

