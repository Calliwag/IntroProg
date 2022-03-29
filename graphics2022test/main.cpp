#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

int main()
{
    Graphics g("Test", 1024, 768);
    double x = 50;
    double y = 50;
    double dirx = 1;
    double diry = 0;
    while (g.draw())
    {
        g.ellipse({100,100}, 5, 5);
        g.ellipse({x,y}, 5, 5);
        g.cout << x <<","<< y <<" : "<< dirx <<","<< diry;
        if(x != 100 && y != 100)
        {
            dirx +=.1/(100-x);
            diry +=.1/(100-y);
        }
        x += dirx;
        y += diry;
    }

    return 0;
}

