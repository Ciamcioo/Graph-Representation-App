#include <iostream>
#include "graphRepresentation/GraphIM.h" 
using namespace std;


int main() {
    GraphIM graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.printMatrix();
    return 0; 
}
