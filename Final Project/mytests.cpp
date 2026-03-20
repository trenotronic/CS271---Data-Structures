//========================================================
// mytests.cpp
// Tren Meckel 
// December 18, 2024
//
// Description:
// This file contains the tests cases for the Graph class 
// And MinPriorityQueue class.
//========================================================
#include "Graph.hpp"
#include "PriorityQueue.hpp"
#include <cassert>

#include <iostream>
using namespace std;

Graph createSampleGraph();

// Test Graph Functions
bool testcheck_edge();
bool testcheck_vertex();
bool testis_empty();
bool testaddEdge();
bool testremoveEdge();
bool testedgeIn();
bool testaddvertex();
bool testremoveVertex();
bool testgetVertices();
bool testgetEdges();
bool testBFS();
bool testDFS();
bool testgetOrdering();
bool testreadFromSTDIN();
bool testDijkstra();

// Test MinPriorityQueue
bool testHeapifyUp();
bool testHeapifyDown();
bool testinsert();
bool testextractMin();
bool testdecreaseKey();
bool testisEmpty();

// Testing Functions
void testingGraph();
void testingMinPriorityQueue();

//==============================================================
// main
// Initiate testing by calling testing methods.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - 0
//==============================================================
int main() 
{

    cout << "\n\nTesting Graph Methods:" << endl;
    testingGraph();
    cout << "\n\nTesting MinPriorityQueue Methods:" << endl;
    testingMinPriorityQueue();
    
    return 0;
}

//==============================================================
// createSampleGraph
// Makes a Graph to use for testing
// PARAMETERS:
// - none
// RETURN VALUE:
// none
//==============================================================
Graph createSampleGraph() 
{
    Graph g;

    // Add vertices
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);

    // Add edges with weights
    g.addEdge(1, 2, 4.5);
    g.addEdge(1, 3, 2.0);
    g.addEdge(2, 3, 5.5);
    g.addEdge(2, 4, 10.0);
    g.addEdge(3, 5, 3.1);
    g.addEdge(4, 6, 11.0);
    g.addEdge(5, 4, 4.8);
    g.addEdge(5, 6, 5.5);

    return g;
}

// *******************************************************
// **************GRAPH TESTING FUNCTIONS******************
// *******************************************************

//==============================================================
// testcheck_edge
// Tests the check_edge function of the Graph class. It verifies 
// whether the function correctly identifies the presence or 
// absence of an edge between two vertices.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testcheck_edge() 
{
    Graph g = createSampleGraph();
    if (!g.edgeIn(1, 2)) return false; 
    if (g.edgeIn(2, 1)) return false; 
    return true;
}

//==============================================================
// testcheck_vertex
// Tests the check_vertex function of the Graph class. It verifies 
// whether the function correctly identifies the presence or 
// absence of a vertex in the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testcheck_vertex() 
{
    Graph g = createSampleGraph();
    auto vertices = g.getVertices();

    // Check for existing vertex
    if (find(vertices.begin(), vertices.end(), 3) == vertices.end()) return false;

    // Check for non-existent vertex
    if (find(vertices.begin(), vertices.end(), 10) != vertices.end()) return false;

    return true;
}

//==============================================================
// testis_empty
// Tests the is_empty function of the Graph class. It verifies 
// whether the function correctly determines if the graph is empty.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testis_empty() 
{
    Graph g; // Empty graph
    if (!g.getVertices().empty()) return false;

    g.addVertex(1); // Add a vertex
    if (g.getVertices().empty()) return false;

    return true;
}

//==============================================================
// testaddEdge
// Tests the addEdge function of the Graph class. It verifies 
// whether the function correctly adds an edge between two vertices.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testaddEdge() 
{
    Graph g = createSampleGraph();
    g.addEdge(2, 6, 7.3); // Add an edge

    // Verify edge addition
    if (!g.edgeIn(2, 6)) return false;
    return true;
}

//==============================================================
// testremoveEdge
// Tests the removeEdge function of the Graph class. It verifies 
// whether the function correctly removes an edge between two vertices.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testremoveEdge() 
{
    Graph g = createSampleGraph();
    g.removeEdge(1, 2); // Remove edge

    // Verify edge removal
    if (g.edgeIn(1, 2)) return false;
    return true;
}

//==============================================================
// testedgeIn
// Tests the edgeIn function of the Graph class. It verifies 
// whether the function correctly returns the weight of an edge.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testedgeIn() 
{
    Graph g = createSampleGraph();

    // Check existing edge
    if (!g.edgeIn(3, 5)) return false;

    // Check non-existent edge
    if (g.edgeIn(5, 3)) return false;

    return true;
}

//==============================================================
// testaddVertex
// Tests the addVertex function of the Graph class. It verifies 
// whether the function correctly adds a vertex to the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testaddVertex() 
{
    Graph g = createSampleGraph();
    g.addVertex(7); // Add a new vertex

    auto vertices = g.getVertices();
    if (find(vertices.begin(), vertices.end(), 7) == vertices.end()) return false;

    return true;
}

//==============================================================
// testremoveVertex
// Tests the removeVertex function of the Graph class. It verifies 
// whether the function correctly removes a vertex and its associated edges.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testremoveVertex() 
{
    Graph g = createSampleGraph();
    g.removeVertex(3); 

    auto vertices = g.getVertices();
    if (find(vertices.begin(), vertices.end(), 3) != vertices.end()) return false;

    return true;
}

//==============================================================
// testgetVertices
// Tests the getVertices function of the Graph class. It verifies 
// whether the function returns all vertices in the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testgetVertices() 
{
    Graph g = createSampleGraph();
    auto vertices = g.getVertices();
    sort(vertices.begin(), vertices.end()); // Ensure order for comparison

    vector<int> expected = {1, 2, 3, 4, 5, 6};
    if (vertices != expected) return false;

    return true;
}

//==============================================================
// testgetEdges
// Tests the getEdges function of the Graph class. It verifies 
// whether the function returns all edges in the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testgetEdges() 
{
    Graph g = createSampleGraph();
    
    // Case 1: Vertex with outgoing edges
    auto edges1 = g.getEdges(1);
    vector<pair<int, double>> expected1 = {{2, 4.5}, {3, 2.0}};
    if (edges1 != expected1) return false;

    // Case 2: Vertex with no outgoing edges
    auto edges2 = g.getEdges(6);
    vector<pair<int, double>> expected2 = {};
    if (edges2 != expected2) return false;

    // Case 3: Non-existent vertex (should throw)
    try {
        g.getEdges(7);
        return false; // If no exception is thrown, the test fails
    } catch (const vertex_exception &) {
        return true; // Exception caught as expected
    }
}

//==============================================================
// testBFS
// Tests the breadthFirstSearch (BFS) function of the Graph class.
// It verifies whether BFS correctly calculates distances from a
// start vertex to all reachable vertices.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testBFS()
{
    // Create a sample graph
    Graph g = createSampleGraph();

    // Perform BFS starting from vertex 1
    auto bfsResult = g.breadthFirstSearch(1);

    // Expected output: {vertex, (parent, distance)}
    // Based on the graph created in createSampleGraph
    unordered_map<int, pair<int, int>> expected = {
        {1, {-1, 0}},  // Start vertex: no parent, distance 0
        {2, {1, 1}},   // Vertex 2: parent is 1, distance 1
        {3, {1, 1}},   // Vertex 3: parent is 1, distance 1
        {4, {2, 2}},   // Vertex 4: parent is 2, distance 2
        {5, {3, 2}},   // Vertex 5: parent is 3, distance 2
        {6, {4, 3}}    // Vertex 6: parent is 4, distance 3
    };

    // Compare the result with expected output
    if (bfsResult != expected) {
        cout << "Test failed. BFS Result:\n";
        for (const auto& [vertex, data] : bfsResult) {
            cout << "Vertex: " << vertex << " Parent: " << data.first
                      << " Distance: " << data.second << "\n";
        }

        cout << "Expected Result:\n";
        for (const auto& [vertex, data] : expected) {
            cout << "Vertex: " << vertex << " Parent: " << data.first
                      << " Distance: " << data.second << "\n";
        }

        return false;
    }

    return true;
}

//==============================================================
// testDFS
// Tests the depthFirstSearch (DFS) function of the Graph class.
// It verifies whether DFS correctly discovers and finishes vertices
// while traversing the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testDFS()
{
    Graph g = createSampleGraph();

    // Perform DFS on the graph
    auto dfsResult = g.depthFirstSearch(true);

    vector<int> expectedOrder = {1, 2, 3, 5, 4, 6};

    // Ensure the returned topological ordering matches the expected order
    vector<int> returnedOrder = g.getOrdering();

    if (returnedOrder != expectedOrder)
    {
        cout << "Test failed: The topological ordering is incorrect!" << endl;
        return false;
    }

    return true;
}

//==============================================================
// testgetOrdering
// Tests the getOrdering function of the Graph class. It verifies whether
// the function correctly generates a topological ordering of vertices in the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testgetOrdering()
{
    Graph g = createSampleGraph();

    // Expected topological order
    vector<int> expectedOrder = {1, 2, 3, 5, 4, 6};

    // Perform DFS and get the topological ordering
    vector<int> order = g.getOrdering();

    // Check if the returned order matches the expected order
    if (order != expectedOrder)
    {
        return false;
    }

    return true;
}

//==============================================================
// testreadFromSTDIN
// Tests the readFromSTDIN function of the Graph class. It verifies whether
// the graph is correctly constructed from user-provided input.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testreadFromSTDIN()
{
    string input = "3 2\n1 2 4\n2 3 5\n";
    istringstream in(input);
    cin.rdbuf(in.rdbuf());

    Graph g = Graph::readFromSTDIN();

    // Verify number of vertices
    if (g.getVertices().size() != 3) return false;

    // Check edges for vertex 1
    auto edges1 = g.getEdges(1);
    if (edges1.size() != 1 || edges1[0].first != 2 || edges1[0].second != 4) return false;

    // Check edges for vertex 2
    auto edges2 = g.getEdges(2);
    if (edges2.size() != 1 || edges2[0].first != 3 || edges2[0].second != 5) return false;

    return true;
}

//==============================================================
// testDijkstra
// Tests the Dijkstra function of the Graph class. It verifies whether
// the function calculates the shortest paths from a given start vertex
// to all other vertices in the graph.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false otherwise
//==============================================================
bool testDijkstra() {
    Graph g;

    // Different Graph
    g.addEdge(1, 2, 4.5);
    g.addEdge(1, 3, 2.0);
    g.addEdge(2, 4, 5.0);
    g.addEdge(3, 5, 3.1);
    g.addEdge(4, 5, 1.0);
    g.addEdge(5, 6, 2.0);

    // Run Dijkstra starting from vertex 1
    auto result = g.dijkstra(1);

    // Expected output based on the graph setup
    // Format: (Node, Predecessor, Distance)
    // Expected distances:
    // 1 -> 0 (start point, no predecessor)
    // 2 -> 1 (distance 4.5)
    // 3 -> 1 (distance 2.0)
    // 4 -> 2 (distance 9.5)
    // 5 -> 3 (distance 5.1)
    // 6 -> 5 (distance 7.1)

    bool testPassed = true;
    
    // Check each node's result
    for (const auto& entry : result) {
        int node = entry.first;
        int prevNode = entry.second.first;
        double dist = entry.second.second;

        // Validate the results for each node
        switch (node) {
            case 1:
                if (dist != 0 || prevNode != -1) {
                    testPassed = false;
                }
                break;
            case 2:
                if (dist != 4.5 || prevNode != 1) {
                    testPassed = false;
                }
                break;
            case 3:
                if (dist != 2.0 || prevNode != 1) {
                    testPassed = false;
                }
                break;
            case 4:
                if (dist != 9.5 || prevNode != 2) {
                    testPassed = false;
                }
                break;
            case 5:
                if (dist != 5.1 || prevNode != 3) {
                    testPassed = false;
                }
                break;
            case 6:
                if (dist != 7.1 || prevNode != 5) {
                    testPassed = false;
                }
                break;
            default:
                break;
        }
    }

    return testPassed;
}

// *******************************************************
// *********MIN PRIORITY QUEUE TESTING FUNCTIONS**********
// *******************************************************

//==============================================================
// testHeapifyUp
// Tests the heapifyUp function of the Min PriorityQueue class.
// Verifies whether the function correctly restores the heap property
// after an element is added to the priority queue by moving it upwards.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the heap property is correctly restored after heapifyUp.
// - false otherwise
//==============================================================
bool testHeapifyUp() 
{
    MinPriorityQueue<int> pq;
    pq.insert(10, 10);
    pq.insert(5, 5);
    pq.insert(15, 15);
    
    // After inserting 10, 5, 15, the min heap should have the following structure:
    // (5,5), (10,10), (15,15)
    
    // We extract the minimum and ensure that 5 is the root.
    auto minElement = pq.extractMin();
    if (minElement.first != 5 || minElement.second != 5) {
        cerr << "testHeapifyUp failed." << endl;
        return false;
    }
    return true;
}

//==============================================================
// testHeapifyDown
// Tests the heapifyDown function of the Min PriorityQueue class.
// Verifies whether the function correctly restores the heap property
// after the minimum element is removed from the priority queue
// by moving elements downwards.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the heap property is correctly restored after heapifyDown.
// - false otherwise
//==============================================================
bool testHeapifyDown() 
{
    MinPriorityQueue<int> pq;
    pq.insert(10, 10);
    pq.insert(5, 5);
    pq.insert(15, 15);
    
    // The heap should reorder after extractMin() is called
    pq.extractMin(); // Removes (5, 5), now root should be (10, 10)
    
    // Now the heap should be (10, 10), (15, 15)
    // After calling extractMin again, the next minimum should be 10
    auto minElement = pq.extractMin();
    if (minElement.first != 10 || minElement.second != 10) {
        cerr << "testHeapifyDown failed." << endl;
        return false;
    }
    return true;
}

//==============================================================
// testinsert
// Tests the insert function of the Min PriorityQueue class.
// Verifies whether the function correctly inserts a new element
// into the priority queue and maintains the heap property.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the element is inserted correctly and the heap property is maintained.
// - false otherwise
//==============================================================
bool testinsert() 
{
    MinPriorityQueue<int> pq;
    pq.insert(10, 10);
    pq.insert(5, 5);
    
    // The heap should reorder to (5, 5), (10, 10)
    auto minElement = pq.extractMin();
    if (minElement.first != 5 || minElement.second != 5) {
        cerr << "testInsert failed." << endl;
        return false;
    }
    return true;
}

//==============================================================
// testextractMin
// Tests the extractMin function of the Min PriorityQueue class.
// Verifies whether the function correctly removes and returns the minimum element
// from the priority queue and maintains the heap property after extraction.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the minimum element is correctly removed and the heap property is maintained.
// - false otherwise
//==============================================================
bool testextractMin() 
{
    MinPriorityQueue<int> pq;
    pq.insert(10, 10);
    pq.insert(5, 5);
    
    // Extract min should return (5, 5)
    auto minElement = pq.extractMin();
    if (minElement.first != 5 || minElement.second != 5) {
        cerr << "testExtractMin failed." << endl;
        return false;
    }
    
    // After extracting 5, now (10, 10) should be the root
    minElement = pq.extractMin();
    if (minElement.first != 10 || minElement.second != 10) {
        cerr << "testExtractMin failed on second extract." << endl;
        return false;
    }
    
    return true;
}

//==============================================================
// testdecreaseKey
// Tests the decreaseKey function of the Min PriorityQueue class.
// Verifies whether the function correctly decreases the key of a specific
// element and restores the heap property if necessary.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the key is correctly decreased and the heap property is maintained.
// - false otherwise
//==============================================================
bool testdecreaseKey() 
{
    MinPriorityQueue<int> pq;

    // Insert elements into the priority queue
    pq.insert(10, 10);  // (value, priority)
    pq.insert(20, 20);
    pq.insert(30, 30);

    // Decrease the key of element 20
    pq.decreaseKey(20, 5);  // Set priority of 20 to 5

    // After decreasing the key, (20, 5) should be the root, as it has the smallest priority.
    pair<int, double> minElem = pq.extractMin();  // Extract the minimum element

    // Verify the heap property
    if (minElem.first == 20 && minElem.second == 5) {
        // If (20, 5) is extracted first, the test passes
        return true;
    } else {
        return false;
    }
}

//==============================================================
// testisEmpty
// Tests the isEmpty function of the Min PriorityQueue class.
// Verifies whether the function correctly identifies whether the priority queue
// is empty or not.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if isEmpty correctly identifies the state of the priority queue.
// - false otherwise
//==============================================================
bool testisEmpty() 
{
    MinPriorityQueue<int> pq;
    assert(pq.isEmpty() == true);  // Initially, it should be empty
    
    pq.insert(10, 10);
    assert(pq.isEmpty() == false); // After insertion, it should not be empty
    
    pq.extractMin();
    assert(pq.isEmpty() == true);  // After extraction, it should be empty again
    
    return true;
}

// *******************************************************
// **********TESTING GRAPH & MIN PRIORITY QUEUE***********
// *******************************************************

//==============================================================
// testingGraph
// Testing functions and respective outputs for Graph class. Updates
// and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void testingGraph() 
{
    struct TestResult
    {
            int passed;
            int failed;
    };
    TestResult Graph_result = {0, 0};
    
    
    if(testcheck_edge() == true)
    {
            cout << "Check edge for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testcheck_vertex() == true)
    {
            cout << "Check vertex for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testis_empty() == true)
    {
            cout << "is_empty for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testaddEdge() == true)
    {
            cout << "Add edge for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testremoveEdge() == true)
    {
            cout << "Remove edge for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testedgeIn() == true)
    {
            cout << "Edge in for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testaddVertex() == true)
    {
            cout << "Add vertex for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testremoveVertex() == true)
    {
            cout << "Remove vertex for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testgetVertices() == true)
    {
            cout << "Get vertices for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testgetEdges() == true)
    {
            cout << "Get edges for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testBFS() == true)
    {
            cout << "BFS for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testDFS() == true)
    {
            cout << "DFS for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testgetOrdering() == true)
    {
            cout << "GetOrdering for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testreadFromSTDIN() == true)
    {
            cout << "readFromSTDIN for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    if(testDijkstra() == true)
    {
            cout << "Dijkstra for Graph test passed" << endl;
            Graph_result.passed++;
    }else{
            Graph_result.failed++;
         }
    
    cout << "\n\n";
    cout << "Graph Tests Passed: " << Graph_result.passed << endl;
    cout << "Graph Tests Failed: " << Graph_result.failed << endl;
    cout << "\n\n";
}

//==============================================================
// testingMinPriorityQueue
// Testing functions and respective outputs for MinPriorityQueue
// class. Updates and outputs the tally of passed and failed tests.
// PARAMETERS: 
// - none
// RETURN VALUE: 
// - none
//==============================================================
void testingMinPriorityQueue() 
{
    struct TestResult
    {
            int passed;
            int failed;
    };
    TestResult MinPQ_result = {0, 0};

    
    if(testHeapifyUp() == true)
    {
            cout << "HeapifyUp for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    if(testHeapifyDown() == true)
    {
            cout << "HeapifyDown for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    if(testinsert() == true)
    {
            cout << "Insert for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    if(testextractMin() == true)
    {
            cout << "ExtractMin for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    if(testdecreaseKey() == true)
    {
            cout << "DecreaseKey for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    if(testisEmpty() == true)
    {
            cout << "IsEmpty for MinPQ test passed" << endl;
            MinPQ_result.passed++;
    }else{
            MinPQ_result.failed++;
         }
    
    cout << "\n\n";
    cout << "MinPQ Tests Passed: " << MinPQ_result.passed << endl;
    cout << "MinPQ Tests Failed: " << MinPQ_result.failed << endl;
    cout << "\n\n";
}
    


