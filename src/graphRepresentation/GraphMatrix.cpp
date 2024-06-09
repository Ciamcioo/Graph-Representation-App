#include "GraphMatrix.h"
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

/**
 * Aditional structure for Kruskal's algorithm of minimal spaning tree which represents the edge of the graph
 */
struct Edge {
    int src, dest, weight;
};
 
/**
 * Construcotor of GraphIM class which as an arguemtn takes the number of verticis 
 * Based on the number of vertices inetrnal matrix is generated with initalization of data
 */
Graph_Matrix::Graph_Matrix(int num_vertrics){ 
    vertices = num_vertrics;
    adj_matrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        adj_matrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adj_matrix[i][j] = INT_MAX;
        }
    } 
}

/**
 * Destrutcotr of the GraphIM class. Release the memory whenever the object is being destroied 
 */
Graph_Matrix::~Graph_Matrix() { 
    for (int i = 0; i < vertices; i++) 
        delete [] adj_matrix[i];
    delete[] adj_matrix;
}

/**
 * Function adds the edge representation to the matrix representing the weights and direction of edges.
 */
void Graph_Matrix::add_edge(int u, int v, int weight) {
   adj_matrix[u][v] = weight;

}
        
/**
 * Function removes the edge between the vertex passed as the arguments. The function sets cell representing the edge between
 * the vertex to the defaults value.
 */
void Graph_Matrix::remove_edge(int u, int v) {
   adj_matrix[u][v] = INT_MAX;
}

/**
 * Function prints to the default output stream matrix where cells represent the edges between the vertexs.
 * Edges have weight which is represented as the number in the array cell.
 */
void Graph_Matrix::print_matrix() const {
   for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++){
            if (adj_matrix[i][j] ==  INT_MAX) {
                std::cout << "0 ";
            } 
            else {
                std::cout << adj_matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
   } 
}

/**
 * Find the next vertex to opearte on
 */
int min_key(int* key, bool* mst_set, int vertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++) {
       if (!mst_set[v] && key[v] < min)
           min = key[v], min_index = v;
    }
    return min_index; 
}

/**
 * Prints the minimum spinning tree which was created
 */
void print_mst(int* parent,int vertices, int** adj_matrix) {
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i< vertices; i++) {
        if(adj_matrix[i][parent[i]] != INT_MAX) {
            std::cout << parent[i] << " - " << i << " \t" << adj_matrix[i][parent[i]] << std::endl;
        }
   } 
}


/**
 * Function implementing prime algorithm for minimal spinning tree
 * Function iterates over the array of vertex to find vertexes which haven't already been used to build minimal spaning tree,
 * checks for the smallest value of neighbour edge and moves to the next vertex.
 * At the end it invokes function which prints and free the memeory which have been used allocated for components of algorithm.
 */
void Graph_Matrix::prim_mst() const {
    int* parent = new int[vertices];    
    int* key = new int[vertices];
    bool* mst_set = new bool[vertices];

    for (int i = 0; i < vertices; i++) 
        key[i] = INT_MAX, mst_set[i] = false;
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int i = 0; i < vertices - 1; i++) {
        int u = min_key(key, mst_set, vertices);
        mst_set[u] = true;
        for (int v = 0; v < vertices; v++) {
            if (adj_matrix[u][v] != INT_MAX && !mst_set[v] && adj_matrix[u][v] < key[v])
                parent[v] = u, key[v] = adj_matrix[u][v];
        }
    }
    

    print_mst(parent, vertices, adj_matrix);

    delete [] parent;
    delete [] key;
    delete [] mst_set;       
}

/**
 * Function which allows to make comparison of two edges 
 */
bool compare_edges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

/**
 * Function creates the minimal spaning tree based on the Kruskal's algorithm. Firstly function fills the edge array with the data and sorts it. 
 * Edges are sorted in increamanting way. Then the edges are added to the union_set which will be merged with other to created minimal spaning tree.
 */
void Graph_Matrix::kruskla_mst() const {
    Edge* edges = new Edge[vertices * vertices];
    int edge_count = 0;

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (adj_matrix[i][j] != INT_MAX) {
                edges[edge_count++] = {i, j, adj_matrix[i][j]};
            }
        }
    }

    std::sort(edges, edges + edge_count, compare_edges);
    
    UnionFind uf(vertices);
    Edge* result = new Edge[vertices];
    int e = 0;

    for (int i = 0; i < edge_count; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int set_u = uf.find(u);
        int set_v = uf.find(v);

        if (set_u != set_v) {
            result[e++] = edges[i];
            uf.union_sets(set_u, set_v);
        }
    }

    // Prints the result of kruskal's mst algorithm
    std::cout << "Following are the edges n the constructed MST:\n";
    for (int i = 0; i < e; i++)
       std::cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << "\n"; 
    delete [] edges;
    delete [] result;
}

/**
 * Function implements the Dijkstra's algorithm to find the shortest path to every single vertex from source vertex.
 * Source vertex is passed to the function as an arugment. 
 * After function calculates the shortest way it displaies it onto the screen.
 * At the very end function frees the memory used for calculations.
 */
void Graph_Matrix::dijkstra(int src) const {
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

    for (int v = 0; v < vertices; ++v) 
        if (!sptSet[v] && adj_matrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adj_matrix[u][v] < dist[v])
            dist[v] = dist[u] + adj_matrix[u][v];
    }
    std::cout << "Vertex Distance from Source " << src << "\n";
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
void Graph_Matrix::bellman_ford(int src) const {
    int* dist = new int[vertices];
    for (int i = 0; i < vertices; ++i) 
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= vertices-1; ++i) {
        for (int u = 0; u < vertices; ++u ) {
            for( int v = 0; v < vertices; ++v) {
                if (adj_matrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adj_matrix[u][v] < dist[v]) 
                    dist[v] = dist[u] + adj_matrix[u][v];
            }
        }
    }

    for (int u = 0; u < vertices; ++u) {
        for (int v = 0; v < vertices; ++v) {
            if (adj_matrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adj_matrix[u][v] < dist[v]) {
                std::cout << "Graph contains negative weight cycle" << std::endl; 
                delete [] dist;
                return;
            }
        }
    }
    
    std::cout << "Vertex Distance from source (calculated with Bellman Ford's algorithm): " << src << std::endl;
    for (int i = 0; i < vertices; i++)
        std::cout << i << "\t" << dist[i] << std::endl;
    
    delete [] dist;
}

/// @brief Function checks if specified vertex exists
/// @param vertex - number of vertex to check 
/// @return Function rutunrs true if vertex exists in other case returns false
bool Graph_Matrix::check_if_vertex_exist(int vertex) const  {
    return (vertex >= 0 && vertex <= vertices) ? true : false;
}

/// @brief Function checks if edge exists in graph
/// @param u - vertex where edge begins
/// @param v - vertex where edge ends 
/// @return Function returns true if egde exists in other case reutnrs false
bool Graph_Matrix::has_edge(int u, int v) const {
    if ( u >=0 && u < vertices && v >= 0 && v < vertices)
        return adj_matrix[u][v] != INT_MAX;
    return false;
}

/// @brief Function returns the weight of a edge
/// @param u  - vertex where edge begins
/// @param v  - vertex where edge ends
/// @return Function returns integera value representing weight of an edge
int Graph_Matrix::get_weight(int u, int v) const {
    return adj_matrix[u][v];
}



