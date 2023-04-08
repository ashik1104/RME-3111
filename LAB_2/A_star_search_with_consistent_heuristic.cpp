#include <bits/stdc++.h>
#include "priority_queue.h"
using namespace std;

// A* Search algorithm //
/* Admissible and consistent heuristic is mandatory for this algorithm. */
/* As heuristic is consistent we don't need to explore a node more than one time.
                              We have done it using visited array */

/* As consistent heuristic is mandatory for this algorithm, it creates wrong output when
                              heuristic is not consistent. */

vector<int> heuristic(1000000);
vector<int> parent(1000000, -1);
vector<int> visited(1000000);
vector<long long int> d(1000000, 1e18); // distance array

class graph
{
    int vertices;
    vector<pair<int, long long int>> *adj_list;

public:
    graph(int v)
    {
        this->vertices = v;
        adj_list = new vector<pair<int, long long int>>[vertices];
    }

    void add_edge(int n1, int n2, long long w)
    {
        adj_list[n1].push_back({n2, w}); // Edit here for directed and undirected //
    }

    int A_star_search(int source, int destination)
    {
        Priority_Queue<pair<long long int, int>> pq;
        pq.push({heuristic[source], source});
        d[source] = 0;

        while (!pq.empty())
        {
            pair<int, int> cost_vs_node = pq.top();
            pq.pop();
            int selected_node = cost_vs_node.second;

            if (selected_node == destination)
            {
                return d[destination];
            }

            if (visited[selected_node])
            {
                continue;
            }

            visited[selected_node] = 1;

            for (auto p : adj_list[selected_node])
            {
                int cost = p.second;
                int adj_node = p.first;
                if ((d[selected_node] + cost) < d[adj_node])
                {
                    d[adj_node] = d[selected_node] + cost;
                    pq.push({(d[adj_node] + heuristic[adj_node]), adj_node});
                    parent[adj_node] = selected_node;
                }
            }
        }
        return -1;
    }
};

void print_optimal_path(int des)
{
    if (parent[des] != -1)
    {
        print_optimal_path(parent[des]);
    }
    cout << des << " ";
}

int main()
{
    freopen("input.txt", "r", stdin);
    int V, E;
    cin >> V >> E;

    graph g(V);

    for (int i = 0; i < E; i++)
    {
        int n1, n2;
        long long w;
        cin >> n1 >> n2 >> w;
        g.add_edge(n1, n2, w);
    }

    int source, destination;
    cin >> source >> destination;

    for (int i = 0; i < V; i++)
    {
        int h_val;
        cin >> h_val;
        heuristic[i] = h_val;
    }

    int cost = g.A_star_search(source, destination);

    if (cost == -1)
    {
        cout << "Destination is not found" << endl;
    }
    else
    {
        cout << "Optimal path : ";
        print_optimal_path(destination);
        cout << endl;
        cout << "Cost : " << cost << endl;
    }
}

/*

5 7
0 1 2
0 2 4
1 2 1
1 3 4
2 3 2
2 4 6
3 4 3

0 4

7 5 5 3 0
7 4 5 2 0
8 3 7 2 0


4 9
0 0 3
0 1 1
0 2 3
1 1 5
1 2 1
1 3 4
2 3 1
2 3 6
2 0 4

0 3

3 2 1 0

*/