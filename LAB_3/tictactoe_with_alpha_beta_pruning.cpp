#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// Tic_Tac_Toe Using Alpha-Beta Pruning....//

int steps = 0;

struct Move
{
    int row, col;
};

class tic_tac_toe
{
public:
    char human, computer, grid[3][3];

    tic_tac_toe()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }

    void play()
    {
        while (true)
        {
            cout << "Which symbol (X or O, X goes first)? : ";
            cin >> human;
            if (human == 'X' or human == 'O')
            {
                break;
            }
            else
            {
                cout << "Please enter Capital 'X' or Capital 'O'" << endl;
            }
        }
        cout << endl;
        print_grid();
        cout << endl;

        computer = human == 'X' ? 'O' : 'X';
        if (human == 'O')
        {
            cout << "AI is making a move......." << endl;
            Sleep(2000);
            computer_move();
            print_grid();
            cout << endl;
        }

        while (true)
        {
            Human_move();
            print_grid();
            cout << endl;

            if (win())
            {
                cout << "Human Wins" << endl;
                return;
            }
            else if (tie())
            {
                cout << "Match Tied" << endl;
                cout << endl;
                return;
            }

            cout << "AI is making a move......." << endl;
            Sleep(2000);
            computer_move();
            print_grid();
            cout << endl;

            if (win())
            {
                cout << "AI Wins" << endl;
                cout << endl;
                return;
            }
            else if (tie())
            {
                cout << "Match Tied" << endl;
                cout << endl;
                return;
            }
        }
    }

    void Human_move()
    {
        while (true)
        {
            cout << "Enter an empty cell(1-9) : ";
            int cell;
            cin >> cell;
            int r = (cell - 1) / 3, c = (cell - 1) % 3;
            if (cell >= 1 and cell <= 9 and grid[r][c] == ' ')
            {
                grid[r][c] = human;
                break;
            }
            else
            {
                cout << cell << " is not empty.." << endl;
            }
        }
    }

    void computer_move()
    {
        Move best_move = find_best_move();
        grid[best_move.row][best_move.col] = computer;
        cout << "With alpha beta pruning recursion steps needed for AI : " << steps << endl;
        steps = 0;
    }

    int min_value(int alpha, int beta)
    {
        int v = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = human;
                    v = min(v, value(alpha, beta, true));
                    grid[i][j] = ' ';
                    if (v <= alpha)
                    {
                        return v;
                    }
                    beta = min(beta, v);
                }
            }
        }
        return v;
    }

    int max_value(int alpha, int beta)
    {
        int v = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = computer;
                    v = max(v, value(alpha, beta, false));
                    grid[i][j] = ' ';
                    if (v >= beta)
                    {
                        return v;
                    }
                    alpha = max(alpha, v);
                }
            }
        }
        return v;
    }

    int value(int alpha, int beta, bool maximizer)
    {
        steps++;
        if (win())
        {
            if (!maximizer)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        if (tie())
        {
            return 0;
        }
        if (maximizer)
        {
            return max_value(alpha, beta);
        }
        else
        {
            return min_value(alpha, beta);
        }
    }

    int minimax(bool maximizer)
    {
        return value(-1000, 1000, maximizer);
    }

    Move find_best_move()
    {
        int best_val = -1000;
        Move best_move;
        best_move.row = -1;
        best_move.col = -1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = computer;
                    int return_value = minimax(false);
                    grid[i][j] = ' ';
                    if (return_value > best_val)
                    {
                        best_val = return_value;
                        best_move.row = i;
                        best_move.col = j;
                    }
                }
            }
        }
        return best_move;
    }

    bool win()
    {
        for (int i = 0; i < 3; i++)
        {
            if (grid[i][0] != ' ' and grid[i][0] == grid[i][1] and grid[i][0] == grid[i][2])
            {
                return true;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (grid[0][i] != ' ' and grid[0][i] == grid[1][i] and grid[0][i] == grid[2][i])
            {
                return true;
            }
        }
        if (grid[0][0] != ' ' and grid[0][0] == grid[1][1] and grid[0][0] == grid[2][2])
        {
            return true;
        }
        if (grid[0][2] != ' ' and grid[0][2] == grid[1][1] and grid[0][2] == grid[2][0])
        {
            return true;
        }

        return false;
    }

    bool tie()
    {
        if (win())
        {
            return false;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void print_grid()
    {
        for (int i = 0; i < 3; i++)
        {
            if (i)
            {
                cout << "-------------" << endl;
            }
            for (int j = 0; j < 3; j++)
            {
                if (j)
                {
                    cout << "||";
                }
                cout << ' ';
                if (grid[i][j] == ' ')
                {
                    cout << 3 * i + j + 1;
                }
                else
                {
                    cout << grid[i][j];
                }
                cout << ' ';
            }
            cout << endl;
        }
    }
};

int main()
{
    tic_tac_toe T;
    T.play();
}