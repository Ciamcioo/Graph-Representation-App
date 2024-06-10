#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H
#include "../algorithmAdditionalElements/UnionFind.h"
#include <limits>
class Graph_Matrix {
    private:
       int vertices;
       int** adj_matrix;
    public:
        // Constructor 
        Graph_Matrix(int num_vertrics);
        // Destructor
        ~Graph_Matrix();
        // Add edge
        void add_edge(int u, int v, int weight);
        // Remove edge
        void remove_edge(int u, int v); 
        // Print list
        void print_matrix() const; 
        // Prim's Algorithm to find MST
        double prim_mst() const;
        //  Kruskla's Algorithm to find MST
        double kruskla_mst() const;
        // Dijkstra's algorithm to find shortest paths from the vertex
        double dijkstra(int src) const;
        // Belman-Ford Algorithm to find shortest paths from the vertex
        double bellman_ford(int src) const; 
        // Function checks if vertex exists
        bool check_if_vertex_exist(int vertex) const;
        // Function checks if an edge exists
        bool has_edge(int u, int v) const;
        // Function returns teh weight of an edge
        int get_weight(int u, int v) const;
        int** get_adj_matrix() const;
        bool get_smaller_edge(int u, int v) const;
};

#endif
