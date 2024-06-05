#include "UnionFind.h"
 
/**
 * Function implementing the UnionFind constructor which as an arguemnt takse the size of the set.
 * Additional the values of the parent and rank are field with default values
 */
UnionFind::UnionFind(int size) {
    n = size; 
    parent = new int[n];  
    rank = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

/**
 * Function implements the UnionFind destructor which release the memory taken for the parent and rank array in case object is being destroied.
 */
UnionFind::~UnionFind() {
    delete [] parent;
    delete [] rank;
}

/**
 * Find function is supposed to find the root of the set to which element 'u' belongs to.
 * It uses the recurention to go through the set and compare the next elements. 
 * The root will be returned as soon as it will be found.
 */
int UnionFind::find(int u) {
    if (u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

/**
 * Function implements union of two sets to which 'u' and 'v' belongs to. 
 * Function is supposed firstly to find the parents of 'u' and 'v' and then compare them to make the correct union. 
 */
void UnionFind::union_sets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    
    if (root_u != root_v) {

        if (rank[root_u] > rank[root_v] ) {
            parent[root_v] = root_u;
        }

        else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        }

        else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}
