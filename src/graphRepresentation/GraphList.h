#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#include "../algorithmAdditionalElements/UnionFind.h"
class GraphList{
    private:
        struct Node {
            int vertex;
            int weight;
            Node* next;
        };
        int vertices;
        Node** adj_list;
        
        void print_mst(int* parent) const;
        int min_key(int* key, bool* mst_set) const;

    public:
        // Constructor
        GraphList(int num_vertices);
        // Destructor
        ~GraphList();
        // Add edge
        void add_edge(int u, int v, int weight, bool directed);
        // Remove edge
        void remove_edge(int u, int v); 
        // Print list
        void print_list() const; 
        // Prim's Algorithm to find MST
        void prim_mst() const;
        //  Kruskla's Algorithm to find MST
        void kruskla_mst() const;
        // Dijkstra's algorithm to find shortest paths from the vertex
        void dijkstra(int src) const;
        // Belman-Ford Algorithm to find shortest paths from the vertex
        void Bellman_ford(int src) const; 
};
#endif 