#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H
#include "../algorithmAdditionalElements/UnionFind.h"
class GraphMatrix {
    private:
       int vertices;
       int** adj_matrix;
    public:
        // Constructor 
        GraphMatrix(int num_vertrics);
        // Destructor
        ~GraphMatrix();
        // Add edge
        void add_edge(int u, int v, int weight);
        // Remove edge
        void remove_edge(int u, int v); 
        // Print list
        void print_matrix() const; 
        // Prim's Algorithm to find MST
        void prim_mst() const;
        //  Kruskla's Algorithm to find MST
        void kruskla_mst() const;
        // Dijkstra's algorithm to find shortest paths from the vertex
        void dijkstra(int src) const;
        // Belman-Ford Algorithm to find shortest paths from the vertex
        void bellman_ford(int src) const; 
        bool check_if_vertex_exist(int vertex) const;
        
};

#endif
