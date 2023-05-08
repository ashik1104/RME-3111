#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// Tic_Tac_Toe from youtube...//

int steps = 0;

struct Move
{
    int row, col, score;
};

class tic_tac_toe
{
public:
    char player, computer, grid[3][3];

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
            cin >> player;
            if (player == 'X' or player == 'O')
            {
                break;
            }
            else
            {
                cout << "Please enter Capital 'X' or Capital 'O'" << endl;
            }
        }

        computer = player == 'X' ? 'O' : 'X';
        if (player == 'O')
        {
            cout << "AI is making a move......." << endl;
            Sleep(2000);
            computer_move();
        }
        print_grid();
        while (true)
        {
            player_move();
            print_grid();
            if (win())
            {
                cout << "player wins" << endl;
                return;
            }
            else if (tie())
            {
                cout << "Tie" << endl;
                return;
            }

            cout << "AI is making a move......." << endl;
            Sleep(2000);
            computer_move();
            print_grid();
            if (win())
            {
                cout << "AI wins" << endl;
                return;
            }
            else if (tie())
            {
                cout << "Tie" << endl;
                return;
            }
        }
    }

    void player_move()
    {
        while (true)
        {
            cout << "Enter an empty cell(1-9) : ";
            int cell;
            cin >> cell;
            int r = (cell - 1) / 3, c = (cell - 1) % 3;
            if (cell >= 1 and cell <= 9 and grid[r][c] == ' ')
            {
                grid[r][c] = player;
                break;
            }
        }
    }

    void computer_move()
    {
        Move best_move = minimax(true);
        grid[best_move.row][best_move.col] = computer;
        cout << steps << endl;
        steps = 0;
    }

    Move minimax(bool maximizer)
    {
        steps++;
        Move best_move;
        if (win())
        {
            if (!maximizer)
            {
                best_move.score = 1;
            }
            else
            {
                best_move.score = -1;
            }
            return best_move;
        }
        else if (tie())
        {
            best_move.score = 0;
            return best_move;
        }

        best_move.score = maximizer ? -1000 : 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = maximizer ? computer : player;
                    Move board_state = minimax(!maximizer);
                    grid[i][j] = ' ';
                    if (maximizer)
                    {
                        if (board_state.score > best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.row = i;
                            best_move.col = j;
                        }
                    }
                    else
                    {
                        if (board_state.score < best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.row = i;
                            best_move.col = j;
                        }
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
                // cout << "-----------" << endl;
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