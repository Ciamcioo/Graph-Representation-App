#ifndef UNION_FIND_H
#define UNION_FIND_H

class UnionFind {
    private:
        int* parent;
        int* rank;
        int n;
    public:
        // UnionFind constructor
        UnionFind(int size);
        // UnionFind destructor
        ~UnionFind();
        // Find the root of the set in which element 'u' belongs
        int find(int u);
        // Make a union of two sets
        void union_sets(int u, int v);
};
#endif 

