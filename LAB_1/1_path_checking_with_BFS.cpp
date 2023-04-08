#include <bits/stdc++.h>
using namespace std;

class graph
{
    int vertices;
    vector<int> *adj_list;

public:
    graph(int v)
    {
        this->vertices = v;
        adj_list = new vector<int>[vertices];
    }

    void add_edge(int n1, int n2)
    {
        adj_list[n1].push_back(n2);
    }

    bool BFS(int source, int destination)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;
        bool found = false;

        q.push(source);
        visited[source] = true;

        while (!q.empty())
        {
            int front_val = q.front();
            q.pop();
            if (front_val == destination)
            {
                found = true;
                return found;
            }

            for (auto adj_node : adj_list[front_val])
            {
                if (!visited[adj_node])
                {
                    visited[adj_node] = true;
                    q.push(adj_node);
                }
            }
        }
        return found;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);

    int v, e;
    cin >> v >> e;

    graph g(v);

    for (int i = 0; i < e; i++)
    {
        int n1, n2;
        cin >> n1 >> n2;
        g.add_edge(n1, n2);
    }

    int q;
    cin >> q;

    cout << endl
         << endl;

    while (q--)
    {
        int source, destination;
        cin >> source >> destination;
        bool chk = g.BFS(source, destination);
        if (chk)
        {
            cout << source << " --> " << destination << " : YES" << endl;
        }
        else
        {
            cout << source << " --> " << destination << " : NO" << endl;
        }
    }

    cout << endl
         << endl;
}