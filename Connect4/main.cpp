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

int main()
{

    int x = 800;
    int y = 800;
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
            board[ix][iy] = ix*iy;
        }
    }

    Vec2d current{x/16,y/16};
    int currentPlayer = 0;

    while (g.draw())
    {
        //        for(int iy = 0; iy < 6; iy++)
        //        {
        //            for(int ix = 0; ix < 7; ix++)
        //            {
        //                if(board[ix][iy] >= 10)
        //                {
        //                    g.cout << "   " << board[ix][iy];
        //                }
        //                else
        //                {
        //                    g.cout << "     " << board[ix][iy];
        //                }
        //            }
        //            g.cout << endl;
        //        }

        if(currentPlayer == 0)
        {
            Color currentColor = YELLOW;
        }

        if(currentPlayer == 1)
        {
            Color currentColor = RED;
        }

        for(int i = 1; i < 8; i++)
        {
            g.line({i*x/8, 0},{i*x/8,y});
            g.line({0,i*y/8},{x,i*y/8});
        }

        g.ellipse(current, x/8, y/8);

        //        if (g.isKeyPressed(Key::Left) && !(current.x < x/16))
        //        {
        //            current.x -= x/8;
        //        }
        //        if (g.isKeyPressed(Key::Right) && !(current.x > 15*x/16))
        //        {
        //            current.x += x/8;
        //        }

        for (const Event& e : g.events())
        {
            g.cerr << e << endl;
            switch (e.evtType)
            {
            case EvtType::KeyPress:

                if(e.arg == static_cast<int>(Key::Left))
                {
                    current.x -= x/8;
                }

                if(e.arg == static_cast<int>(Key::Right))
                {
                    current.x += x/8;
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

