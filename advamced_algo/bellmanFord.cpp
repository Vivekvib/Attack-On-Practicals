#include <iostream>
#include <vector>
#include <climits> // Required for INT_MAX
using namespace std;

struct Edge {
    int u, v, w;   // from, to, weight
};

int main() {
    int V, E, src;
    
    // 1. Input Graph Data
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter each edge as: u v weight\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    cout << "Enter source vertex: ";
    cin >> src;

    // 2. Initialize Distances
    // We use a large number (INT_MAX) to represent infinity
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // 3. Relaxation Step
    // We repeat this (V-1) times. In the worst case, a shortest path 
    // can traverse at most V-1 edges.
    for (int i = 1; i <= V - 1; i++) {
        for (auto &e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // 4. Check for Negative Weight Cycles
    // If we can still relax an edge after V-1 iterations, a negative cycle exists.
    
    for (auto &e : edges) {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
            cout << "\nGraph contains a NEGATIVE WEIGHT CYCLE!\n";
            return 0;
        }
    }

    // 5. Output Result
    cout << "\nShortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << " -> INF\n";
        else
            cout << "Node " << i << " -> " << dist[i] << "\n";
    }

    return 0;
}

//5,8,0 1 -1,0 2 4,1 2 3,1 3 2,1 4 2,3 2 5,3 1 1,4 3 -3,0//
