#include <bits/stdc++.h>
using namespace std;

#define ios ios_base::sync_with_stdio(false)
#define fast_input cin.tie(0)
#define fast_output cout.tie(0)

#define INF 1e18
#define NINF -1e18

#define pdi pair<double, int>

vector<double> node_weight(1000, INF);
vector<double> node_probability(1000);

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

    pdi exp_value(int node)
    {
        double val = 0;
        for (auto adj_node : adj_list[node])
        {
            double probability = 0.5;
            pdi p = value(adj_node, true);
            val += probability * p.first;
        }
        return {val, node};
    }

    pdi max_value(int node)
    {
        double val = NINF;
        int most_eligible_chance_node = -1;
        for (auto adj_node : adj_list[node])
        {
            pdi p = value(adj_node, false);
            if (p.first > val)
            {
                val = p.first;
                most_eligible_chance_node = adj_node;
            }
        }
        return {val, most_eligible_chance_node};
    }

    pdi value(int node, bool maximizing_player)
    {
        if (node_weight[node] != INF)
        {
            return {node_weight[node], node};
        }
        else if (maximizing_player)
        {
            return max_value(node);
        }
        else
        {
            return exp_value(node);
        }
    }

    pdi minimax(int node, bool maximizing_player)
    {
        return value(node, maximizing_player);
    }
};

int main()
{
    ios;
    fast_input;
    fast_output;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int V, E;
    cin >> V >> E;

    graph g(V);

    for (int i = 0; i < E; i++)
    {
        double n1, n2;
        cin >> n1 >> n2;
        g.add_edge(n1, n2);
    }

    for (int i = 4; i < V; i++)
    {
        double terminal_val;
        cin >> terminal_val;
        node_weight[i] = terminal_val;
    }

    pdi optimal = g.minimax(0, true);
    cout << "Expected maximum value of root node : " << optimal.first << endl;
    cout << "Expected maximum reward node : " << optimal.second << endl;
}