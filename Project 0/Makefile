list: DoublyLinkedList.cpp DoublyLinkedList.hpp
	g++ DoublyLinkedList.cpp -c -o doublylinkedlist 

mytests: list mytests.o
	g++ -o mytests mytests.o doublylinkedlist
	./mytests

mytests.o: mytests.cpp
	g++ -o mytests.o mytests.cpp -c

clean:
	rm mytests.o doublylinkedlist mytests