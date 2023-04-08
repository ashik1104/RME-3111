#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// AI VS AI....//
// Bumblebee VS Devastator........//

int steps = 0;

struct Move
{
    int row, col;
};

class tic_tac_toe
{
public:
    char Bumblebee, Devastator, grid[3][3];

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
            cout << "Hey coward Devastator choice is always yours....." << endl;
            cout << "Shut up Bumblebee.....I will destroy you..." << endl;
            cout << "Hahahahaha...let's see...." << endl;
            cout << "Which symbol (X or O, X goes first)? : " << endl;

            Devastator = rand() % 2 == 0 ? 'X' : 'O';
            cout << "Devastator chooses : " << Devastator << endl;
            cout << endl;

            if (Devastator == 'X' or Devastator == 'O')
            {
                break;
            }
            else
            {
                cout << "Please enter Capital 'X' or Capital 'O'" << endl;
            }
        }

        Bumblebee = Devastator == 'X' ? 'O' : 'X';
        if (Devastator == 'O')
        {
            cout << "Bumblebee is making a move......." << endl;
            Sleep(2000);
            Bumblebee_move();
        }
        print_grid();
        cout << endl;
        while (true)
        {
            cout << "Devastator is making a move......" << endl;
            Sleep(2000);
            Devastator_move();
            print_grid();
            cout << endl;
            if (win())
            {
                cout << "I am Devastator. No one can beat me..." << endl;
                return;
            }
            else if (tie())
            {
                cout << "It's tie...." << endl;
                cout << endl;
                return;
            }

            cout << "Bumblebee is making a move......." << endl;
            Sleep(2000);
            Bumblebee_move();
            print_grid();
            cout << endl;
            if (win())
            {
                cout << "Hahaha Devastator...you don't know about me. I am the boss." << endl;
                return;
            }
            else if (tie())
            {
                cout << "It's tie...." << endl;
                cout << endl;
                return;
            }
        }
    }

    void Bumblebee_move()
    {
        Move best_move = find_best_move_for_Bumblebee();
        grid[best_move.row][best_move.col] = Bumblebee;
        cout << "With alpha beta pruning recursion steps : " << steps << endl;
        steps = 0;
    }

    void Devastator_move()
    {
        Move best_move = find_best_move_for_Devastator();
        grid[best_move.row][best_move.col] = Devastator;
        cout << "With alpha beta pruning recursion steps : " << steps << endl;
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
                    grid[i][j] = Devastator;
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
                    grid[i][j] = Bumblebee;
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

    Move find_best_move_for_Bumblebee()
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
                    grid[i][j] = Bumblebee;
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

    Move find_best_move_for_Devastator()
    {
        int best_val = 1000;
        Move best_move;
        best_move.row = -1;
        best_move.col = -1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = Devastator;
                    int return_value = minimax(true);
                    grid[i][j] = ' ';
                    if (return_value < best_val)
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