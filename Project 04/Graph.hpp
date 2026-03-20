//========================================================
// Graph.hpp 
// James Bui & Kien Le & Tren Meckel 
// December 9, 2024
//
// Description: 
// This header file defines the Graph class, which represents a graph 
// using an adjacency list. The class provides methods for adding vertices, 
// adding edges, and performing depth-first search (DFS) and breadth-first 
// search (BFS). The DFS implementation supports tracking discovery and 
// finish times for each vertex and returns an ordering of vertices based 
// on the traversal. The graph also supports retrieving the order of 
// vertices for tasks such as topological sorting.
//========================================================
#include <iostream>
#include <list>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <vector>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "customexceptions.hpp"

using namespace std;

class Graph
{
private:
    unordered_map<int, vector<int> > Adj;
    vector<int> sorted;
    vector<int> order;

    bool check_vertex(int u) const;
    bool check_edge(int u, int v) const;
    bool is_empty() const;

    void DFS_visit(int u, unordered_map<int, tuple<int, int, int>> &DFS, int &time, bool sort);

public:
    Graph();
    Graph(const Graph &G);
    ~Graph();
    Graph &operator=(const Graph &G);

    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool edgeIn(int u, int v);
    void deleteVertex(int u);
    void addVertex(int u);

    unordered_map<int, pair<int, int> > breadthFirstSearch(int s);
    unordered_map<int, tuple<int, int, int> > depthFirstSearch(bool sort = false);
    vector<int> getOrdering();

    static Graph readFromSTDIN();
};

#endif
