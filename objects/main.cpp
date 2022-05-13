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

    if(pos.y >= g.height()-width/2)
    {
        vel.y *= -1;
        pos.y = g.height()-width/2;
        c++;
    }
    if(pos.x >= g.width()-width/2)
    {
        vel.x *= -1;
        pos.x = g.width()-width/2;
        c++;
    }
    if(pos.y <= width/2)
    {
        vel.y *= -1;
        pos.y = width/2;
        c++;
    }
    if(pos.x <= width/2)
    {
        vel.x *= -1;
        pos.x = width/2;
        c++;
    }

//    vel.y += .1;

    pos += vel;

    if(c == 0)
    {
        return 0;
    }

    return 1;
}

int collide(vector<objct>& objcts, vector<vector<int>>& col)
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

            if((objcts[ix].pos-objcts[iy].pos).magnitude() <= (objcts[ix].width+objcts[iy].width)/2/* && (col[ix][iy] == 0 || col[ix][iy] == 1)*/)
            {

                double totalVel = (objcts[ix].vel + objcts[iy].vel).magnitude()+.00001;
                double initVel = objcts[ix].vel.magnitude() + objcts[iy].vel.magnitude();

//                double xFrac = totalVel*objcts[iy].width*objcts[iy].massMult/(objcts[ix].width*objcts[ix].massMult+objcts[iy].width*objcts[iy].massMult);
//                double yFrac = totalVel*objcts[ix].width*objcts[ix].massMult/(objcts[ix].width*objcts[ix].massMult+objcts[iy].width*objcts[iy].massMult);

                double xFrac = totalVel*pow(objcts[iy].width,2)*objcts[iy].massMult/(pow(objcts[ix].width,2)*objcts[ix].massMult+pow(objcts[iy].width,2)*objcts[iy].massMult);
                double yFrac = totalVel*pow(objcts[ix].width,2)*objcts[ix].massMult/(pow(objcts[ix].width,2)*objcts[ix].massMult+pow(objcts[iy].width,2)*objcts[iy].massMult);

//                double cool = xFrac+yFrac;

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

                double finVel = objcts[ix].vel.magnitude() + objcts[iy].vel.magnitude();

                double mult = (initVel/finVel);

//                if((objcts[ix].massMult > 0) && (objcts[iy].massMult > 0))
//                {
                    objcts[ix].vel = objcts[ix].vel * mult;
                    objcts[iy].vel = objcts[iy].vel * mult;
//                }

//                dirX = objcts[ix].vel*(1/(objcts[ix].vel.magnitude()+.000001));
//                dirY = objcts[iy].vel*(1/(objcts[iy].vel.magnitude()+.000001));

//                objcts[ix].vel = -1*objcts[ix].vel;
//                objcts[iy].vel = -1*objcts[iy].vel;

                objcts[ix].pos += dirX*((objcts[iy].width-(objcts[ix].pos-objcts[iy].pos).magnitude())/2);
                objcts[iy].pos += dirY*((objcts[ix].width-(objcts[ix].pos-objcts[iy].pos).magnitude())/2);

                col[ix][iy]++;

                count++;
            }
            else if(!((objcts[ix].pos-objcts[iy].pos).magnitude() <= (objcts[ix].width+objcts[iy].width)/2))
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

double total(vector<objct> objcts)
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

    vector<vector<int>> col;

    vector<objct> objcts;

    int n = 500;

    col.resize(n);

    for(int i = 0; i < col.size(); i++)
    {
        col[i].resize(n);
    }

    objcts.resize(n);

    for(int i = 0; i < n; i++)
    {
        objcts[i].pos = {g.randomInt(0,g.width()),g.randomInt(0,g.height())};
//        objcts[i].pos = {g.randomInt(100,100),g.randomInt(100,g.height()-100)};
        objcts[i].vel = {g.randomDouble(-1,1),g.randomDouble(-1,1)};
//        objcts[i].vel = {g.randomDouble(0,0),g.randomDouble(0,1)};
        objcts[i].width = g.randomDouble(10,10);
        objcts[i].massMult=g.randomDouble(1,1);

        objcts[i].vel = objcts[i].vel*(g.randomDouble(1,1)/objcts[i].vel.magnitude());
    }

    objcts[n-1].vel = objcts[n-1].vel*100;
//    objcts[n-1].vel = {0,1};
    objcts[n-1].massMult=1000000000;
    objcts[n-1].color = BLUE;

//    vector<int> graph{};

    double gravity = 0.00;

    double colCon = 1;

    vector<double> graph;

    while (g.draw())
    {
        for(int i = 0; i < objcts.size(); i++)
        {
            objcts[i].update(g);
        }

        collide(objcts, col);

        double b1 = total(objcts);

        graph.push_back(b1);

        for(int i = 0; i < objcts.size(); i++)
        {
//           objcts[i].vel = objcts[i].vel*mult;
           objcts[i].draw(g);
        }

        colDet(objcts, colCon);

//        CoM(g, objcts);
        if(gravity != 0)
        {
            grav(objcts, gravity);
        }

        int n = 2;

        for(int i = 0; i < graph.size(); i += n)
        {
            g.line({i/n,graph[i]/10},{i/n+1,graph[i+n]/10}, RED);
        }

        g.cout <<b1;
    }

    return 0;
}


