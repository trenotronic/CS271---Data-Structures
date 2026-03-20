//========================================================
// Graph.cpp
// James Bui & Kien Le & Tren Meckel
// December 9, 2024
//
// Description:
// This source file implements the methods of the Graph class as
// defined in Graph.hpp.
//========================================================
#include "Graph.hpp"
using namespace std;

//==============================================================
// Graph
// Default constructor for the Graph class. Initializes an empty
// graph with no vertices or edges.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
Graph::Graph() {};

//==============================================================
// Graph
// Copy constructor for the Graph class. Creates a deep copy of
// the given graph, duplicating its adjacency list and sorted order.
// PARAMETERS:
// - G: A reference to the Graph object to copy.
// RETURN VALUE:
// - none
//==============================================================
Graph::Graph(const Graph &G)
{
    Adj = G.Adj;
    sorted = G.sorted;
};

//==============================================================
// ~Graph
// Destructor for the Graph class. Frees any dynamically allocated
// resources (if applicable).
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
Graph::~Graph() {};

//==============================================================
// operator=
// Assignment operator for the Graph class. Copies the adjacency
// list and sorted order from the given graph.
// PARAMETERS:
// - G: A reference to the Graph object to copy.
// RETURN VALUE:
// - A reference to the updated Graph object.
//==============================================================
Graph &Graph::operator=(const Graph &G)
{
    Adj = G.Adj;
    sorted = G.sorted;
    return *this;
};

//==============================================================
// check_vertex
// Checks if a given vertex exists in the graph.
// PARAMETERS:
// - u: The vertex to check.
// RETURN VALUE:
// - true if the vertex exists, false otherwise.
//==============================================================
bool Graph::check_vertex(int u) const
{
    return Adj.find(u) != Adj.end();
}

//==============================================================
// check_edge
// Checks if a directed edge exists between two vertices.
// PARAMETERS:
// - u: The source vertex.
// - v: The destination vertex.
// RETURN VALUE:
// - true if the edge exists, false otherwise.
//==============================================================
bool Graph::check_edge(int u, int v) const
{
    if (!check_vertex(u))
    {
        return false;
    }
    for (int i = 0; i < Adj.at(u).size(); i++)
    {
        if (Adj.at(u)[i] == v)
        {
            return true;
        }
    }
    return false;
}

//==============================================================
// is_empty
// Checks if the graph is empty.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the graph is empty, false otherwise.
//==============================================================
bool Graph::is_empty() const
{
    return sorted.empty();
}

//==============================================================
// addEdge
// Adds a directed edge from vertex `u` to vertex `v`. If either vertex
// does not exist or the edge already exists, no action is taken.
// PARAMETERS:
// - u: The source vertex.
// - v: The destination vertex.
// RETURN VALUE:
// - none
//==============================================================
void Graph::addEdge(int u, int v)
{
    if (!check_vertex(u))
    {
        return;
    }
    if (!check_vertex(v))
    {
        return;
    }
    if (!check_edge(u, v))
    {
        Adj[u].push_back(v);
    }
    return;
};

//==============================================================
// removeEdge
// Removes a directed edge from vertex `u` to vertex `v`. Throws an
// edge_exception if the edge does not exist.
// PARAMETERS:
// - u: The source vertex.
// - v: The destination vertex.
// RETURN VALUE:
// - none
//==============================================================
void Graph::removeEdge(int u, int v)
{
    for (int i = 0; i < Adj[u].size(); i++)
    {
        if (Adj[u][i] == v)
        {
            Adj[u].erase(Adj[u].begin() + i);
            return;
        };
    };
    throw edge_exception();
};

//==============================================================
// edgeIn
// Checks if a directed edge exists from vertex `u` to vertex `v`
// within the adjacency list.
// PARAMETERS:
// - u: The source vertex.
// - v: The destination vertex.
// RETURN VALUE:
// - true if the edge exists, false otherwise.
//==============================================================
bool Graph::edgeIn(int u, int v)
{
    if (!check_vertex(u))
    {
        return false;
    }
    for (int i = 0; i < Adj[u].size(); i++)
    {
        if (Adj[u][i] == v)
        {
            return true;
        };
    };
    return false;
};

//==============================================================
// deleteVertex
// Deletes a vertex `u` and all edges associated with it. Removes
// any incoming edges to `u` from other vertices.
// PARAMETERS:
// - u: The vertex to delete.
// RETURN VALUE:
// - none
//==============================================================
void Graph::deleteVertex(int u)
{
    Adj.erase(u);
    for (int i = 0; i < sorted.size(); i++)
    {
        if (edgeIn(sorted[i], u))
        {
            removeEdge(sorted[i], u);
        };
    };
};

//==============================================================
// addVertex
// Adds a new vertex to the graph. Throws a vertex_exception if the
// vertex already exists.
// PARAMETERS:
// - u: The vertex to add.
// RETURN VALUE:
// - none
//==============================================================
void Graph::addVertex(int u)
{
    if (check_vertex(u))
    {
        throw vertex_exception();
    };
    sorted.push_back(u);
    Adj.insert({u, vector<int>()});
};

//==============================================================
// breadthFirstSearch
// Performs a breadth-first search (BFS) starting from vertex `s`.
// Tracks the distance of each vertex from `s` and their parent
// vertices in the BFS tree.
// PARAMETERS:
// - s: The starting vertex.
// RETURN VALUE:
// - An unordered_map where each key is a vertex, and the value
//   is a pair (distance, parent).
//==============================================================
unordered_map<int, pair<int, int>> Graph::breadthFirstSearch(int s)
{
    unordered_map<int, pair<int, int>> BFS;
    if (is_empty())
    {
        return BFS;
    };
    for (int i = 0; i < sorted.size(); i++)
    {
        BFS.insert({sorted[i], pair<int, int>(-1, 0)}); // -1 as unreachable, 0 as NIL
    }
    BFS[s].first = 0;
    BFS[s].second = -1;
    queue<int> to_visit;
    to_visit.push(s);
    while (!to_visit.empty())
    {
        int u = to_visit.front();
        to_visit.pop();
        for (int i = 0; i < Adj[u].size(); i++)
        {
            if (BFS[Adj[u][i]].first == -1)
            {
                BFS[Adj[u][i]].first = BFS[u].first + 1;
                BFS[Adj[u][i]].second = u;
                to_visit.push(Adj[u][i]);
            };
        }
    };
    return BFS;
};

//==============================================================
// DFS_visit
// Recursive helper function for depth-first search. Updates the
// discovery and finish times of each vertex and optionally inserts
// vertices into the topological order.
// PARAMETERS:
// - u: The current vertex.
// - DFS: A reference to the map tracking DFS data.
// - time: A reference to the current time counter.
// - sort: A boolean indicating whether to update the topological order.
// RETURN VALUE:
// - none
//==============================================================
void Graph::DFS_visit(int u, unordered_map<int, tuple<int, int, int>> &DFS, int &time, bool sort)
{
    time++;
    get<0>(DFS[u]) = time;

    for (int i = 0; i < Adj.at(u).size(); i++)
    {
        int v = Adj.at(u)[i];
        if (get<0>(DFS[v]) == -1)
        {
            get<2>(DFS[v]) = u;
            DFS_visit(v, DFS, time, sort);
        }
    }
    time++;
    get<1>(DFS[u]) = time;
    if (sort)
    {
        order.insert(order.begin(), u);
    }
}

//==============================================================
// depthFirstSearch
// Performs a depth-first search (DFS) on the graph. Tracks discovery
// and finish times for each vertex and optionally generates a
// topological ordering.
// PARAMETERS:
// - sort: A boolean indicating whether to generate a topological sort.
// RETURN VALUE:
// - An unordered_map where each key is a vertex, and the value
//   is a tuple (discovery_time, finish_time, parent).
//==============================================================
unordered_map<int, tuple<int, int, int>> Graph::depthFirstSearch(bool sort)
{
    unordered_map<int, tuple<int, int, int>> DFS;
    if (is_empty())
    {
        return DFS;
    };
    for (int i = 0; i < sorted.size(); i++)
    {
        DFS[sorted[i]] = make_tuple(-1, -1, 0); // -1, -1 as time sentinel, 0 as NIL
    };

    int time = 0;
    for (int i = 0; i < sorted.size(); i++)
    {
        if (get<0>(DFS[sorted[i]]) == -1)
        {
            DFS_visit(sorted[i], DFS, time, sort);
        };
    };
    return DFS;
};

//==============================================================
// getOrdering
// Retrieves the vertex order generated by depth-first search.
// Typically used for topological sorting.
// PARAMETERS:
// - none
// RETURN VALUE:
// - A vector of integers representing the vertex order.
//==============================================================
vector<int> Graph::getOrdering()
{
    return order;
};

//==============================================================
// readFromSTDIN
// Reads a graph's vertices and edges from standard input. Expects the
// number of vertices (n) and edges (m) followed by m pairs of integers
// representing directed edges.
// PARAMETERS:
// - none
// RETURN VALUE:
// - A Graph object initialized with the input data.
//==============================================================
Graph Graph::readFromSTDIN()
{
    Graph G;
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        G.addVertex(i);
    }

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        G.addEdge(u, v);
    }
    return G;
};
