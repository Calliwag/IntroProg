#include <iostream>
#include "graphics.h"
#include <iomanip>

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

void drawTable(vector<vector<int>> board, Graphics& g)
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

void drawTableAdvance(vector<vector<int>> board, Graphics& g, int x, int y)
{

    for(int iy = 0; iy < 6; iy++)
    {
        for(int ix = 0; ix < 7; ix++)
        {
            if(board[ix][iy] == 1)
            {
                g.ellipse({ix*x/7+x/14,iy*y/7+3*y/14}, y/7, x/7, YELLOW, YELLOW);
            }
            if(board[ix][iy] == 2)
            {
                g.ellipse({ix*x/7+x/14,iy*y/7+3*y/14}, y/7, x/7, RED, RED);
            }
        }
        g.cout << endl;
    }
}

int drop(int& currentColumn, vector<vector<int>>& board, int& currentPlayer)
{

    int lastPlace = -1;

    for(int i = 0; i < 6; i++)
    {
        if(board[currentColumn][i] == 0)
        {
            lastPlace = i;
        }
        else
        {
            break;
        }
    }
    if(lastPlace == -1)
    {
        return 0;
    }
    board[currentColumn][lastPlace] = currentPlayer + 1;
    return 1;
}

int main()
{

    int x = 600;
    int y = 600;
    Graphics g("Test", x, y);

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
            board[ix][iy] = 0;
        }
    }

    Vec2d current{x/14,y/14};
    int currentPlayer = 0;

    Color currentColor = YELLOW;

    int currentColumn = 0;

    while (g.draw())
    {

        drawTableAdvance(board, g, x, y);

        if(currentPlayer == 0)
        {
            currentColor = YELLOW;
        }

        else if(currentPlayer == 1)
        {
            currentColor = RED;
        }

        for(int i = 1; i < 8; i++)
        {
            g.line({i*x/7, 0},{i*x/7,y});
            g.line({0,i*y/7},{x,i*y/7});
        }

        g.ellipse(current, x/7, y/7, currentColor);

        for (const Event& e : g.events())
        {
            g.cerr << e << endl;
            switch (e.evtType)
            {
            case EvtType::KeyPress:

                if(e.arg == static_cast<int>(Key::Left))
                {
                    current.x -= x/6.98;
                    currentColumn --;
                }

                if(e.arg == static_cast<int>(Key::Right))
                {
                    current.x += x/6.98;
                    currentColumn ++;
                }

                if(e.arg == static_cast<int>(Key::Down))
                {
                    drop(currentColumn, board, currentPlayer);
                    currentPlayer = -currentPlayer + 1;
                }

                break;
            case EvtType::KeyRelease:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::MousePress:
                break;
            case EvtType::MouseRelease:
                break;
            default:
                break;
            }
        }

    }

}

