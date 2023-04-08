#include <bits/stdc++.h>
using namespace std;

#define INF 1e18
#define NINF -1e18
vector<long long int> node_weight(1000, INF);

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

    long long min_value(long long alpha, long long beta, int node)
    {
        long long val = INF;
        for (auto adj_node : adj_list[node])
        {
            val = min(val, value(alpha, beta, adj_node, true));
            if (val <= alpha)
            {
                return val;
            }
            beta = min(beta, val);
        }
        return val;
    }

    long long max_value(long long alpha, long long beta, int node)
    {
        long long val = NINF;
        for (auto adj_node : adj_list[node])
        {
            val = max(val, value(alpha, beta, adj_node, false));
            if (val >= beta)
            {
                return val;
            }
            alpha = max(alpha, val);
        }
        return val;
    }

    long long value(long long alpha, long long beta, int node, bool maximizing_player)
    {
        if (node_weight[node] != INF)
        {
            return node_weight[node];
        }
        else if (maximizing_player)
        {
            return max_value(alpha, beta, node);
        }
        else
        {
            return min_value(alpha, beta, node);
        }
    }

    long long int minimax(long long alpha, long long beta, int node, bool maximizing_player)
    {
        return value(alpha, beta, node, maximizing_player);
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int V, E;
    cin >> V >> E;

    graph g(V);

    for (int i = 0; i < E; i++)
    {
        int n1, n2;
        cin >> n1 >> n2;
        g.add_edge(n1, n2);
    }

    for (int i = 10; i < V; i++)
    {
        long long terminal_val;
        cin >> terminal_val;
        node_weight[i] = terminal_val;
    }

    long long optimal = g.minimax(NINF, INF, 0, true);
    cout << "Optimal Value : " << optimal << endl;
}