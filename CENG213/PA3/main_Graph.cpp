#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    using namespace std;
    Graph g;

    g.InsertVertex("S");
    g.InsertVertex("T");
    g.InsertVertex("X");
    g.InsertVertex("Y");
    g.InsertVertex("Z");

    g.ConnectVertices("S", "T", 10);
    g.ConnectVertices("S", "Y", 4);
    g.ConnectVertices("S", "Z", 7);
    g.ConnectVertices("T", "Y", 3);
    g.ConnectVertices("X", "Y", 9);
    g.ConnectVertices("T", "X", 1);
    g.ConnectVertices("Y", "Z", 2);
    g.ConnectVertices("X", "Z", 5);
    g.ConnectVertices("Z", "S", 7);

    g.PrintAll();
    // std::vector<int> res;
    // const string from = "S";
    // const string to = "Z";
    // g.ShortestPath(res, from, to);
    
    
    
    
    // g.InsertVertex("A");
    // g.InsertVertex("B");
    // g.InsertVertex("C");
    // g.InsertVertex("D");
    // g.InsertVertex("E");
    // g.InsertVertex("F");
    // g.InsertVertex("G");
    // g.InsertVertex("H");
    // g.InsertVertex("I");
    // g.InsertVertex("J");

    // g.ConnectVertices("A", "B", 1);
    // g.ConnectVertices("A", "C", 2);
    // g.ConnectVertices("A", "D", 3);
    // g.ConnectVertices("A", "E", 4);
    // g.ConnectVertices("A", "F", 5);
    // g.ConnectVertices("A", "G", 6);
    // g.ConnectVertices("A", "H", 7);
    // g.ConnectVertices("A", "I", 8);

    // try
    // {
    //     g.ConnectVertices("A", "J", 9);
    // }
    // catch(const TooManyEdgeOnVertexExecption& e)
    // {
    //     std::cout << e.what() << '\n';
    // }
    return 0;
}