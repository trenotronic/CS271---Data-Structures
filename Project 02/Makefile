all: mytests

BSTNode: BSTNode.cpp BSTNode.hpp customexceptions.hpp
	g++ -c BSTNode.cpp -o BSTNode.o

BST: BST.cpp BST.hpp BSTNode.hpp customexceptions.hpp
	g++ -c BST.cpp -o BST.o

RBTreeNode: RBTreeNode.cpp RBTreeNode.hpp customexceptions.hpp
	g++ -c RBTreeNode.cpp -o RBTreeNode.o

RBTree: RBTree.cpp RBTree.hpp RBTreeNode.hpp customexceptions.hpp
	g++ -c RBTree.cpp -o RBTree.o

mytests: BSTNode BST RBTreeNode RBTree mytests.cpp customexceptions.hpp
	g++ -c mytests.cpp -o mytests.o
	g++ -o mytests BSTNode.o BST.o RBTreeNode.o RBTree.o mytests.o
	./mytests

clean:
	rm -f *.o mytests