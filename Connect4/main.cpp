#include <iostream>
#include "graphics.h"
#include <iomanip>

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

Graphics g("Test", 1600, 900);

void drawTable(vector<vector<int>> board)
{

    for(int iy = 0; iy < 6; iy++)
    {
        for(int ix = 0; ix < 7; ix++)
        {
            if(board[ix][iy] >= 10)
            {
                g.cout << "   " << board[ix][iy];
            }
            else
            {
                g.cout << "     " << board[ix][iy];
            }
        }
        g.cout << endl;
    }
}

int main()
{

    vector<vector<int>> board;
    board.resize(7);

    for(int ix = 0; ix < 7; ix++)
    {
        board[ix].resize(6);
    }

    for(int ix = 0; ix < 7; ix++)
    {
        for(int iy = 0; iy < 6; iy++)
        {
            board[ix][iy] = ix*iy;
        }
    }

    while (g.draw())
    {
        for(int iy = 0; iy < 6; iy++)
        {
            for(int ix = 0; ix < 7; ix++)
            {
                if(board[ix][iy] >= 10)
                {
                    g.cout << "   " << board[ix][iy];
                }
                else
                {
                    g.cout << "     " << board[ix][iy];
                }
            }
            g.cout << endl;
        }
    }
    return 0;
}

