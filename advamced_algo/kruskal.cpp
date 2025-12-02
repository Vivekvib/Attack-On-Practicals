#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;
    int w;
};


class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false; 

        // union by rank
        if (rankv[rx] < rankv[ry]) {
            parent[rx] = ry;
        } else if (rankv[rx] > rankv[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rankv[rx]++;
        }
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges as: u v weight\n";
    cout << "(Use 0-based vertex indices: 0 to " << V-1 << ")\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    DSU dsu(V);
    vector<Edge> mst;      
    int totalWeight = 0;   

    for (auto &e : edges) {
        
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.w;
        }
    }


    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (auto &e : mst) {
        cout << e.u << " -- " << e.v << "  (weight = " << e.w << ")\n";
    }
    cout << "Total weight of MST = " << totalWeight << "\n";

    return 0;
}
