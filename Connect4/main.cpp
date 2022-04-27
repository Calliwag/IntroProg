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

int drop(int& currentColumn, vector<vector<int>>& board, int& currentPlayer, int& dropX, int& dropY)
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
    dropX = currentColumn;
    dropY = lastPlace;
    return 1;
}

int checkNorth(vector<vector<int>> b, int currentPlayer, int x, int y)
{
    int c = currentPlayer + 1;

    if(y <= 2)
    {
        if(b[x][y+1] == c && b[x][y+2] == c && b[x][y+3] == c)
        {
            return 1;
        }
    }
    return 0;
}

int checkEastWest(vector<vector<int>> b, int currentPlayer)
{
    int c = currentPlayer + 1;
    int count;

    for(int ix = 0; ix < 7; ix++)
    {
        count = 0;
        for(int iy = 0; iy < 6; iy++)
        {
            if(b[ix][iy] == c)
            {
                count++;
            }
            if(count == 4)
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkDiag(vector<vector<int>> b, int currentPlayer)
{
    int c = currentPlayer + 1;

    for(int ix = 0; ix < 4; ix++)
    {
        for(int iy = 0; iy < 3; iy++)
        {
            if(b[ix][iy] == c && b[ix+1][iy+1] == c && b[ix+2][iy+2] == c && b[ix+3][iy+3] == c)
            {
                return 1;
            }
        }
    }

    for(int ix = 0; ix < 4; ix++)
    {
        for(int iy = 5; iy > 2; iy--)
        {
            if(b[ix][iy] == c && b[ix+1][iy-1] == c && b[ix+2][iy-2] == c && b[ix+3][iy-3] == c)
            {
                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    int dropX = 0;
    int dropY = 0;

    int winner;
    bool win = 0;

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

        g.ellipse(current, x/7, y/7, currentColor, currentColor);

        for (const Event& e : g.events())
        {
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
                    drop(currentColumn, board, currentPlayer, dropX, dropY);

                    if(checkEastWest(board, currentPlayer) == 1)
                    {
                        win = 1;
                        winner = currentPlayer;
                    }
                    if(checkNorth(board, currentPlayer, dropX, dropY) == 1)
                    {
                        win = 1;
                        winner = currentPlayer;
                    }
                    if(checkDiag(board, currentPlayer) == 1)
                    {
                        win = 1;
                        winner = currentPlayer;
                    }
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
        if(win == 1)
        {
            break;
        }

    }

}

