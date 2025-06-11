#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    vector<vector<pair<int, int>>> adj;
    int vertices;

public:
    Graph(int V)
    {
        vertices = V;
        adj.resize(V);
    }

    // undirected graph
    void addEdge(int u, int v, int wt)
    {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    void display()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (auto node : adj[i])
                cout << "(" << node.first << ", " << node.second << ") ";
            cout << endl;
        }
    }

    int spanningTree()
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(vertices, 0);

        // add weight and node to the priority queue
        pq.push({0, 0});
        int sum = 0;

        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node])
                continue;
            vis[node] = 1;
            sum += wt;

            // check for each edge in the adjacency list
            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int edWt = it.second;
                if (!vis[adjNode])
                {
                    pq.push({edWt, adjNode});
                }
            }
        }
        return sum;
    }
};

int main()
{
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.display();

    cout << "Minimum cost of the MST: " << g.spanningTree() << endl;

    return 0;
}