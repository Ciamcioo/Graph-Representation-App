#include "GraphList.h"
#include <iostream> 
#include <climits>
#include <algorithm>
#include <cstring>

struct Edge {
    int src, dest, weight;
};

/**
 * Creates the graph object represented by the array which index points to the first edge of graph and
 * this edge points to next edge etc. At the begining every vertex has no edges, because it is null pointer. 
 */
Graph_List::Graph_List(int num_vertices) {
    vertices = num_vertices;
    adj_list = new Node*[vertices];
    for (int i = 0; i < vertices; i++) {
        adj_list[i] = nullptr;
    }
}

/**
 * Destructor which iterate over the array of vertex and dealocate every edge for this vertex. 
 * At the very end it also dealocate the memory for the arrray.
 */
Graph_List::~Graph_List() {
    for (int i = 0; i < vertices; i++) {
        Node* currentNode = adj_list[i];
        while (currentNode != nullptr) {
            Node* tmp = currentNode;
            currentNode = currentNode->next;
            delete tmp; 
        }
    }
    delete[] adj_list;
}

/**
 * Function add new edge between the u and v vertex by creating a new representation of the Node of 
 * ending vertex and shifting current first edge of the list to the second position. Insert new edge 
 * as the first element of the list.
 */
void Graph_List::add_edge(int u, int v, int weight,bool directed) {
   Node* new_node = new Node{v, weight,  adj_list[u]}; 
   if (!directed) {
        Node* reverse_node = new Node{u, weight, adj_list[v]};
        adj_list[v] = reverse_node;
   }
        
   adj_list[u] = new_node;
}

/**
 * Function removes the edge between the u and v vertex by checking the adj_list of u vertex. Function
 * also handles the fix of the list of edges by changin the node's pointers.
 */
void Graph_List::remove_edge(int u, int v) {
    Node* currentNode = adj_list[u];
    Node* prev = nullptr;
    
    while(currentNode != nullptr && currentNode->vertex !=  v) {
        prev = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr) return; 
    if (prev == nullptr) {
        adj_list[u] = currentNode->next;
    }
    else {
        prev->next = currentNode->next;
    }
    delete currentNode;
}

/**
 * Prints the graph by writing for every vertes of the graph its edges and the ending vertex
 * Functions has the const arguemnt so it indicates that none of object's fields are changed.
 */
void Graph_List::print_list() const {
    for (int i = 0; i < vertices; ++i){
        std::cout << i << ":";
        Node* currentNode = adj_list[i];
        while (currentNode != nullptr) {
            std::cout << " -> " << currentNode->vertex << " (weight " << currentNode->weight << ")";
            currentNode = currentNode->next;
        }
        std::cout << std::endl;
    }
}
/**
 * Function finds the next vertex which haven't been added to the minimal spining tree yet.
 */
int Graph_List::min_key(int* key, bool* mst_set) const  {
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++) {
        if (!mst_set[v] && key[v] < min)
            min = key[v], min_index = v;
    }
    return min_index;
}
/**
 * Function prints the minimal spining tree
 */
void Graph_List::print_mst(int* parent) const {
    std::cout << "Edge \t Weight\n";
    for (int i = 1; i < vertices; i++) {
        Node* currentNode = adj_list[parent[i]];
        while (currentNode != nullptr) {
            if (currentNode->vertex == i) {
                std:: cout << parent[i] << " - " << i << "\t" << currentNode->weight << std::endl;
                break; 
            }
            currentNode = currentNode->next;
        }
    }
    
}
/**
 * Function implemnts the prim's algorithm to find minimal spining tree for the graph.
 * Allocates additional memory to store the mst and release it as soon as its finish it workes.
 * After establish the minimal spining tree function prints to the default stream the result of its work.
 */
void Graph_List::prim_mst() const {
    int* parent = new int[vertices];
    int* key = new int[vertices];
    bool* mst_set = new bool[vertices];
    
    for (int i = 0; i < vertices; i++) 
        key[i] = INT_MAX, mst_set[i] = false;
    
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < vertices; i++) {
        int u = min_key(key, mst_set); 
        mst_set[u] = true; 

        for (int v = 0; v <vertices; v++) {
            Node* currentNode = adj_list[u];
            while (currentNode != nullptr) {
                if (currentNode->vertex == v && currentNode->weight < key[v] && !mst_set[v]) {
                    parent[v] = u;
                    key[v] = currentNode->weight;
                }
                currentNode = currentNode->next;
            }
        } 
    }   
    
    print_mst(parent);
    
    delete [] parent;
    delete [] key;
    delete [] mst_set;
}

bool compare_edges_list(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

/**
 * Function implements the Dijkstra's algorithm to find the shortest path to every single vertex from source vertex.
 * Source vertex is passed to the function as an arugment. 
 * After function calculates the shortest way it displaies it onto the screen.
 * At the very end function frees the memory used for calculations.
 */
void  Graph_List::kruskla_mst()  const {
    Edge* edges = new Edge[vertices*vertices];
    int edge_index = 0;  
    for (int i = 0; i< vertices; ++i) {
        Node* node = adj_list[i];
        while (node) {
            edges[edge_index++] = {i, node->vertex, node->weight};
            node = node->next;
        }
    }

    std::sort(edges, edges + edge_index, compare_edges_list);

    UnionFind uf(vertices);
    Edge* result = new Edge[vertices-1];
    int result_index = 0;
    
    for (int i = 0; i < edge_index; ++i) {
        int src_root = uf.find(edges[i].src);
        int dest_root = uf.find(edges[i].dest);
        
        if(src_root != dest_root) {
            result[result_index++] = edges[i];
            uf.union_sets(src_root, dest_root);
        }
    }

    std::cout << "Minimum Spanning Tree (Kruskal's Algorithm):\n";
    for (int i = 0; i < edge_index; i++) 
        std::cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight;

    delete [] edges;
    delete [] result;
}

void Graph_List::dijkstra(int src) const { 
    int* dist = new int[vertices];
    bool* sptSet = new bool[vertices];

    for (int i = 0; i < vertices; ++i) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;
    
    for (int count = 0; count < vertices - 1; ++count) {
        int min = INT_MAX, min_index = -1;

        for (int v = 0; v < vertices; ++v) 
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        int u = min_index;
        sptSet[u] = true;

        Node* node = adj_list[u];
        while (node) {
            int v = node->vertex;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + node->weight < dist[v])
                dist[v] = dist[u] + node->weight;
            node = node->next;
        }
    }


    std::cout << "Vertex Distance from Source (calculated with dijkstra's algorithm):  " << src << "\n";
    for (int i = 0; i < vertices; ++i) 
        std::cout << i << "\t" << dist[i] << "\n";
    
    delete [] dist;
    delete [] sptSet;
}

/**
 * Function implements the Bellman Ford's algorithm to find the shortest path to every single vertex from source vertex.
 * Source vertex is passed as an arugemnt from the user.
 * Additionaly function checks for the negative cycle which might appear in the graph.
 * Finaly function prints the result of the calculation and frees the memory that was needed for it.
 */
void Graph_List::bellman_ford(int src) const {
    int* dist = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i <= vertices - 1; ++i) {
        for (int u = 0; u < vertices; ++u) {
            Node* node = adj_list[u];
            while (node) {
                int v = node->vertex;
                int weight = node->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
                node = node->next;
            }
        }
    }

    for (int u = 0; u < vertices; ++u) {
        Node* node = adj_list[u];
        while (node) {
            int v = node->vertex;
            int weight = node->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                std::cout<< "Graph contains negative weight cycle" << std::endl;
                delete[] dist;
                return;
            }
            node = node->next;
        }
    }
    
    std::cout << "Vertex Distance from source (calculated with Bellman Ford's algorithm): " << src << std::endl; 
    for (int i = 0; i < vertices; ++i)
        std::cout << i << "\t" <<  dist[i] << std::endl;
}
bool Graph_List::check_if_vertex_exist(int vertex) const {
    return (vertex >= 0 && vertex <= vertices)? true : false; 
}
    


