#include <bits/stdc++.h>
using namespace std;

// MDP Policy_Iteration

#define fast ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pii pair<int, int>
#define pds pair<double, string>
#define vpii vector<pair<int, int>>
#define NINF -1e9
#define INF 1e9
#define eps 1e-4

double grid[3][4];
vector<string> policy[3];
double GAMMA = 0.9;
map<int, string> actions;

void all_actions()
{
    actions[0] = "U⬆";
    actions[1] = "D⬇";
    actions[2] = "R➡";
    actions[3] = "⬅ L";
}

bool is_valid_state(pii state)
{
    int x = state.first;
    int y = state.second;
    if ((x == 0 and y == 3) or (x == 1 and y == 1) or (x == 1 and y == 3))
    {
        return false;
    }
    return true;
}

bool is_outside_or_wall(pii coordinate)
{
    int x = coordinate.first;
    int y = coordinate.second;
    if (x == 1 and y == 1)
    {
        return true;
    }
    else if (x < 0 or y < 0 or x >= 3 or y >= 4)
    {
        return true;
    }
    return false;
}

double calculate_exp_val(pii state, string action)
{
    // noise = 20%
    double value = 0.0;
    double p_deterministic = 0.8;
    double p_noise = 0.1;
    int x = state.first;
    int y = state.second;
    if (action == "U⬆")
    {
        vpii next_states = {{x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (int i = 0; i < next_states.size(); i++)
        {
            if (i == 0)
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_deterministic * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_deterministic * (GAMMA * grid[nx][ny]));
                }
            }
            else
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_noise * +(GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_noise * (GAMMA * grid[nx][ny]));
                }
            }
        }
        return value;
    }
    else if (action == "D⬇")
    {
        vpii next_states = {{x + 1, y}, {x, y + 1}, {x, y - 1}};
        for (int i = 0; i < next_states.size(); i++)
        {
            if (i == 0)
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_deterministic * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_deterministic * (GAMMA * grid[nx][ny]));
                }
            }
            else
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_noise * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_noise * (GAMMA * grid[nx][ny]));
                }
            }
        }
        return value;
    }
    else if (action == "R➡")
    {
        vpii next_states = {{x, y + 1}, {x - 1, y}, {x + 1, y}};
        for (int i = 0; i < next_states.size(); i++)
        {
            if (i == 0)
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_deterministic * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_deterministic * (GAMMA * grid[nx][ny]));
                }
            }
            else
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_noise * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_noise * (GAMMA * grid[nx][ny]));
                }
            }
        }
        return value;
    }
    else if (action == "⬅ L")
    {
        vpii next_states = {{x, y - 1}, {x - 1, y}, {x + 1, y}};
        for (int i = 0; i < next_states.size(); i++)
        {
            if (i == 0)
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_deterministic * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_deterministic * (GAMMA * grid[nx][ny]));
                }
            }
            else
            {
                if (is_outside_or_wall({next_states[i].first, next_states[i].second}))
                {
                    value += (p_noise * (GAMMA * grid[x][y]));
                }
                else
                {
                    int nx = next_states[i].first;
                    int ny = next_states[i].second;
                    value += (p_noise * (GAMMA * grid[nx][ny]));
                }
            }
        }
        return value;
    }
    return value;
}

double Value_Convergence(pii state)
{
    double value = NINF;
    string action = policy[state.first][state.second];
    if (action == "U⬆")
    {
        double exp_val_for_u = calculate_exp_val(state, action);
        if (exp_val_for_u > value)
        {
            value = exp_val_for_u;
        }
    }
    else if (action == "D⬇")
    {
        double exp_val_for_d = calculate_exp_val(state, action);
        if (exp_val_for_d > value)
        {
            value = exp_val_for_d;
        }
    }
    else if (action == "R➡")
    {
        double exp_val_for_r = calculate_exp_val(state, action);
        if (exp_val_for_r > value)
        {
            value = exp_val_for_r;
        }
    }
    else if (action == "⬅ L")
    {
        double exp_val_for_l = calculate_exp_val(state, action);
        if (exp_val_for_l > value)
        {
            value = exp_val_for_l;
        }
    }
    return value;
}

string policy_Extraction(pii state)
{
    double value = NINF;
    string optimal_action = "";
    for (int i = 0; i < 4; i++)
    {
        string action = actions[i];
        if (action == "U⬆")
        {
            double exp_val_for_u = calculate_exp_val(state, action);
            if (exp_val_for_u > value)
            {
                value = exp_val_for_u;
                optimal_action = "U⬆";
            }
        }
        else if (action == "D⬇")
        {
            double exp_val_for_d = calculate_exp_val(state, action);
            if (exp_val_for_d > value)
            {
                value = exp_val_for_d;
                optimal_action = "D⬇";
            }
        }
        else if (action == "R➡")
        {
            double exp_val_for_r = calculate_exp_val(state, action);
            if (exp_val_for_r > value)
            {
                value = exp_val_for_r;
                optimal_action = "R➡";
            }
        }
        else if (action == "⬅ L")
        {
            double exp_val_for_l = calculate_exp_val(state, action);
            if (exp_val_for_l > value)
            {
                value = exp_val_for_l;
                optimal_action = "⬅ L";
            }
        }
    }

    return optimal_action;
}

void initialize_grid()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 0 and j == 3)
            {
                grid[i][j] = 1;
            }
            else if (i == 1 and j == 3)
            {
                grid[i][j] = -1;
            }
            else if (i == 1 and j == 1)
            {
                grid[i][j] = -500;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }
}

void initialize_policy_vector_size()
{
    for (int i = 0; i < 3; i++)
    {
        policy[i] = vector<string>(4);
    }
}

void initialize_policy()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            policy[i][j] = "U⬆";
        }
    }
}

int main()
{
    fast;

    initialize_grid();
    initialize_policy_vector_size();
    initialize_policy();
    all_actions();

    bool policy_changed = true;
    while (policy_changed)
    {
        initialize_grid();

        // converge value using fixed policy in each loop
        double loop_breaker = 100;
        while (loop_breaker > eps)
        {
            loop_breaker = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (is_valid_state({i, j}))
                    {
                        double value = Value_Convergence({i, j});
                        loop_breaker = max(loop_breaker, abs(value - grid[i][j]));
                        grid[i][j] = value;
                    }
                }
            }
        }

        // Policy_Extraction after every value convergence
        policy_changed = false;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (is_valid_state({i, j}))
                {
                    string p = policy_Extraction({i, j});
                    if(p != policy[i][j])
                    {
                        policy_changed = true;
                    }
                    policy[i][j] = p;
                }
            }
        }
    }


    cout << endl;
    cout << "         Optimal Value of each state : " << endl;
    cout << "        ==============================" << endl;
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 1 and j == 1)
            {
                cout << "WALL"
                     << "\t\t";
            }
            else
            {
                cout << setprecision(2) << grid[i][j] << "\t\t";
            }
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;

    cout << "         Optimal Policy of each state : " << endl;
    cout << "        ===============================" << endl;
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 1 and j == 1)
            {
                cout << "WALL"
                     << "\t\t";
            }
            else if ((i == 0 and j == 3) or (i == 1 and j == 3))
            {
                cout << "EXIT"
                     << "\t\t";
            }
            else
            {
                cout << policy[i][j] << "\t\t";
            }
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;
}