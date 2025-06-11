#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    vector<vector<int>> adj;
    int vertices;

public:
    // constructor
    Graph(int V)
    {
        vertices = V;
        adj.resize(V);
    }

    void buildAdjacencyList(int u, int v)
    {
        adj[u].push_back(v);
    }

    void display()
    {
        for (int i = 1; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int node : adj[i])
                cout << node << " ";

            cout << endl;
        }
    }

    void bfs(int src)
    {
        int visited[vertices] = {0};
        vector<int> ans;
        queue<int> q;
        visited[src] = 1;
        q.push(src);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            ans.push_back(node);
            for (auto it : adj[node])
            {
                if (!visited[it])
                {
                    visited[it] = 1;
                    q.push(it);
                }
            }
        }

        cout << "BFS traversal: ";
        for (auto it : ans)
            cout << it << " ";

        cout << endl;
    }
};

int main()
{
    Graph g(10);
    g.buildAdjacencyList(1, 2);
    g.buildAdjacencyList(1, 6);
    g.buildAdjacencyList(2, 1);
    g.buildAdjacencyList(2, 3);
    g.buildAdjacencyList(2, 4);
    g.buildAdjacencyList(3, 2);
    g.buildAdjacencyList(4, 2);
    g.buildAdjacencyList(4, 5);
    g.buildAdjacencyList(5, 4);
    g.buildAdjacencyList(5, 8);
    g.buildAdjacencyList(6, 1);
    g.buildAdjacencyList(6, 7);
    g.buildAdjacencyList(6, 9);
    g.buildAdjacencyList(7, 6);
    g.buildAdjacencyList(7, 8);
    g.buildAdjacencyList(8, 5);
    g.buildAdjacencyList(8, 7);
    g.buildAdjacencyList(9, 6);

    g.display();
    int src;
    cout << "Enter the source node: ";
    cin >> src;

    g.bfs(src);

    return 0;
}