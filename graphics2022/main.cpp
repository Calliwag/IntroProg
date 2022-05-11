#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

class objct
{
public:

    Vec2d pos{100,100};
    Vec2d vel{0,0};
    bool col = 0;
    double width = 10;
    double massMult = 1;
    Color color = WHITE;

    void draw(Graphics& g);
    int update(Graphics& g);

};

void objct::draw(Graphics& g)
{
    g.ellipse(pos, width, width, color);
}

int objct::update(Graphics& g)
{
    int c = 0;

    if(pos.y >= g.height()-width)
    {
        vel.y *= -1;
        pos.y = g.height()-width;
        c++;
    }
    if(pos.x >= g.width()-width)
    {
        vel.x *= -1;
        pos.x = g.width()-width;
        c++;
    }
    if(pos.y <= width)
    {
        vel.y *= -1;
        pos.y = width;
        c++;
    }
    if(pos.x <= width)
    {
        vel.x *= -1;
        pos.x = width;
        c++;
    }

//    vel.y += .5;

    pos += vel;

    if(c == 0)
    {
        return 0;
    }

    return 1;
}

int collide(vector<objct>& objcts, vector<vector<bool>>& col)
{
    double loss = 0;

    int count = 0;

    for(int ix = 0; ix < objcts.size() - 1; ix++)
    {
        for(int iy = ix + 1; iy < objcts.size(); iy++)
        {
//            if(ix == iy)
//            {
//                iy++;
//            }

            if((objcts[ix].pos-objcts[iy].pos).magnitude() <= (objcts[ix].width+objcts[iy].width)/2 && col[ix][iy] == 0)
            {

                double totalVel = (objcts[ix].vel + objcts[iy].vel).magnitude();

                double xFrac = totalVel*objcts[iy].width*objcts[iy].massMult/(objcts[ix].width*objcts[ix].massMult+objcts[iy].width*objcts[iy].massMult)/2;
                double yFrac = totalVel*objcts[ix].width*objcts[ix].massMult/(objcts[ix].width*objcts[ix].massMult+objcts[iy].width*objcts[iy].massMult)/2;

                double cool = xFrac+yFrac;

//                xFrac /= cool;
//                yFrac /= cool;

//                double xFrac = 1/2;
//                double yFrac = 1/2;

                Vec2d dirX = objcts[ix].pos-objcts[iy].pos;
                Vec2d dirY = objcts[iy].pos-objcts[ix].pos;

                dirX = dirX*(1/dirX.magnitude());
                dirY = dirY*(1/dirY.magnitude());

                objcts[ix].vel += dirX*xFrac;
                objcts[iy].vel += dirY*yFrac;

//                objcts[ix].vel = -1*objcts[ix].vel;
//                objcts[iy].vel = -1*objcts[iy].vel;

                objcts[ix].pos += dirX;
                objcts[iy].pos += dirY;

                col[ix][iy] = 1;

                count++;
            }
            else
            {
                col[ix][iy] = 0;
            }
        }
    }
    return loss;
}

void colDet(vector<objct>& objcts, double n)
{
    for(int ix = 0; ix < objcts.size() - 1; ix++)
    {
        for(int iy = ix + 1; iy < objcts.size(); iy++)
        {
            if(ix == iy)
            {
                iy++;
            }

            if((objcts[ix].pos-objcts[iy].pos).magnitude() <= (objcts[ix].width+objcts[iy].width)/2)
            {

                objcts[ix].vel = objcts[ix].vel*n;
                objcts[iy].vel = objcts[iy].vel*n;

            }
        }
    }
}

void grav(vector<objct>& objcts, double g)
{
    for(int ix = 0; ix < objcts.size(); ix++)
    {
        for(int iy = 0; iy < objcts.size(); iy++)
        {
            if(ix == iy)
            {
                iy++;
            }
                objcts[ix].vel += (g*pow(objcts[iy].width*objcts[iy].massMult/(objcts[ix].width*objcts[ix].massMult),2)/pow((objcts[iy].pos-objcts[ix].pos).magnitude(),2))*(objcts[iy].pos-objcts[ix].pos);
        }
    }
}

double avgSpeed(vector<objct> objcts)
{

    double avg = 0;

    for(int i = 0; i < objcts.size(); i++)
    {
        avg += objcts[i].vel.magnitude();
    }

    avg /= objcts.size();

    return avg;

}

int collisions(Graphics& g, vector<objct> objcts)
{

    double CperP = 0;

    for(int i = 0; i < objcts.size(); i++)
    {
        if(objcts[i].update(g) == 1)
        {
            CperP++;
        }
    }

    return CperP;

}

Vec2d CoM(Graphics& g, vector<objct> objcts)
{

    Vec2d a{0.0,0.0};

    double mass = 0;

    for(int i = 0; i < objcts.size(); i++)
    {
        a += objcts[i].pos*pow(objcts[i].width*objcts[i].massMult,2);
        mass += pow(objcts[i].width*objcts[i].massMult,2);
    }

    a.x /= mass;
    a.y /= mass;

    g.ellipse(a, 3, 3, RED, RED);

    return a;
}

double total(Graphics& g,vector<objct> objcts, double grav)
{

    double count = 0;

    for(int i = 0; i < objcts.size(); i++)
    {
       count += objcts[i].vel.magnitude();
    }

    return count;
}

int main()
{
    Graphics g("Test", 700, 700);

    vector<vector<bool>> col;

    vector<objct> objcts;

    int n = 100;

    col.resize(n);

    for(int i = 0; i < col.size(); i++)
    {
        col[i].resize(n);
    }

    objcts.resize(n);

    for(int i = 0; i < n; i++)
    {
        objcts[i].pos = {g.randomInt(0,g.width()),g.randomInt(0,g.height())};
        objcts[i].vel = {g.randomDouble(-1,1),g.randomDouble(-1,1)};
        objcts[i].width = g.randomDouble(10,10);
        objcts[i].massMult=g.randomDouble(1,1);

        objcts[i].vel = objcts[i].vel*(g.randomDouble(1,1)/objcts[i].vel.magnitude());
    }

    objcts[n-1].vel = objcts[n-1].vel*1;
    objcts[n-1].massMult=1;
    objcts[n-1].color = RED;

    vector<int> graph{};

    double gravity = .0;

    double colCon = 1;

    while (g.draw())
    {
        double b1 = total(g, objcts, gravity);

        for(int i = 0; i < objcts.size(); i++)
        {
            objcts[i].update(g);
        }

        double begin = total(g, objcts, gravity);

        collide(objcts, col);

        double current = total(g, objcts, gravity);

        double mult = begin/current;

        for(int i = 0; i < objcts.size(); i++)
        {
//           objcts[i].vel = objcts[i].vel*mult;
           objcts[i].draw(g);
        }

        double b4 = total(g, objcts, gravity);

        colDet(objcts, colCon);

        double b5 = total(g, objcts, gravity);

//        CoM(g, objcts);

//        grav(objcts, gravity);

        g.cout <<b1<<" "<<begin<<" "<<current<<" "<<b4<<" "<<b5;
    }

    return 0;
}


