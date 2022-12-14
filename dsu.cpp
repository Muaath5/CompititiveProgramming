#include <bits/stdc++.h>
const int maxDSU = 2e5+1;

namespace alg {

class DSU {
    int n = 1; // nodes count

private:
    int cmps = n;
    int* cnt = new int[maxDSU];
    int* parent = new int[maxDSU];

public:
    DSU() {
        initialize();
    }

    DSU(int nodes) {
        n = nodes;
        initialize();
    }

    inline void initialize()
    {
        for (int i = 0; i < n; i++)
        {
            cnt[i] = 1;
            parent[i] = i;
        }
    }

    // Getting the root (base) of a node 
    int root(int node)
    {
        if (parent[node] == node) return node;
        return parent[node] = root(parent[node]);
    }

    bool same_component(int x, int y) {
        return root(x) == root(y);
    }

    int components_count() {
        return cmps;
    }

    // Linking (Unioning) two nodes, returns false if they are connected, otherwise returns true
    bool link(int x, int y)
    {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (cnt[x] > cnt[y])
            std::swap(x, y);
        cnt[y] += cnt[x];
        parent[x] = y;
        return true;
    }
};

}
