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

    void dfs(int srcNode, int *vis, vector<int> &ans)
    {
        vis[srcNode] = 1;
        ans.push_back(srcNode);
        for (auto node : adj[srcNode])
        {
            if (!vis[node])
                dfs(node, vis, ans);
        }
    }

    void dfsOfGraph(int src)
    {
        int visited[vertices] = {0};
        vector<int> ans;
        dfs(src, visited, ans);

        cout << "DFS traversal: ";
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

    g.dfsOfGraph(src);

    return 0;
}