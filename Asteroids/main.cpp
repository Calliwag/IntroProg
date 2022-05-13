#include <iostream>
#include "graphics.h"

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

class ship
{
public:
    double angle = 0;
    Vec2d pos{200,200};
    Vec2d vel{0,0};

    void draw(Graphics& g);
    void update(Graphics& g);
};

void ship::draw(Graphics& g)
{

    vector<Vec2d> ship{{pos.x+10*cos(angle),pos.y+10*sin(angle)},{pos.x+9.5*cos(angle+5*3.14/6),pos.y+9.5*sin(angle+5*3.14/6)},{pos.x-5*cos(angle),pos.y-5*sin(angle)},{pos.x+9.5*cos(angle-5*3.14/6),pos.y+9.5*sin(angle-5*3.14/6)}};

    g.polygon({ship[0],ship[1],ship[2],ship[3],ship[0]}, WHITE);

//    g.cout << vel.magnitude();
}

void ship::update(Graphics& g)
{

    if(g.isKeyPressed(Key::Up))
    {

        double primVel = vel.magnitude();

        vel += {0.05*cos(angle),0.05*sin(angle)};

        double finVel = vel.magnitude();

        if(vel.magnitude() > 3)
        {
            vel = vel*(primVel/finVel);
        }

    }

    if(g.isKeyPressed(Key::Left))
    {
        angle -= .1;
    }

    if(g.isKeyPressed(Key::Right))
    {
        angle += .1;
    }

    pos += vel;
}

class ast
{
public:
    Vec2d pos{300,300};
    Vec2d vel{0.1,0.1};
    vector<Vec2d> points{{20,20},{0,40},{-20,20},{-40,0},{-20,-20},{0,-40},{20,-20},{40,0}};
    double size = 10;
    int invincible = 0;

    void draw(Graphics& g);
    void update(Graphics& g);
    bool edgeCol(Graphics& g);
};

void ast::draw(Graphics& g)
{

    vector<Vec2d> pointS = points;

    for(int i = 0; i < points.size(); i++)
    {
        pointS[i].x = points[i].x+pos.x;
        pointS[i].y = points[i].y+pos.y;
    }

    pointS.push_back(pointS[0]);

    g.polygon(pointS, WHITE);

}

void ast::update(Graphics& g)
{
    pos += vel;

    double avg = 0;

    for(int i = 0; i < points.size(); i++)
    {
        avg += points[i].magnitude();
    }

    avg /= points.size();

    size = avg;

    invincible--;

}



bool colDet1(ast Ast, ship p)
{
    if((p.pos-Ast.pos).magnitude() <= Ast.size)
    {
        return 1;
    }
    return 0;
}

void splitR(Graphics& g,vector<ast>& asts, int n, ship pl)
{

    int lowScore = 1000;

    int p = 0;

    for(int i = 2; i < asts[n].points.size() - 2; i++)
    {
        if((pl.pos-(asts[n].points[i]+asts[n].pos)).magnitude() < lowScore)
        {
            p = i;
            lowScore = (pl.pos-(asts[n].points[i]+asts[n].pos)).magnitude();
        }
    }

    vector<Vec2d> ast1;
    ast1.resize(p);
    vector<Vec2d> ast2;
    ast2.resize(2+asts[n].points.size()-p);

    for(int i = 0; i < p; i++)
    {
        ast1[i]=asts[n].points[i];
    }
    for(int i = p; i < asts[n].points.size(); i++)
    {
        ast2[i]=asts[n].points[i];
    }

    ast2.pop_back();
    ast2.pop_back();

    Vec2d vel1 = {g.randomDouble(-1,1),g.randomDouble(-1,1)};
    Vec2d vel2 = -1*vel1;

//    Vec2d offset = {g.randomDouble(-10,10),g.randomDouble(-10,10)};
    Vec2d offset = {0,0};
    Vec2d avg1;
    for(int i = 0; i < ast1.size(); i++)
    {
        avg1 += ast1[i];
    }

    avg1 = avg1*(1/ast1.size());

    Vec2d avg2;
    for(int i = 0; i < ast2.size(); i++)
    {
        avg2 += ast2[i];
    }

    avg2 = avg2*(1/ast2.size());

    Vec2d pos1 = asts[n].pos + offset;
    Vec2d pos2 = asts[n].pos - offset;

    asts.erase(asts.begin()+5);

//    for(int i = n+1; i < asts.size(); i++)
//    {
//        ast tast = asts[i];
//        asts[i] = asts[i-1];
//        asts[i-1] = tast;
//    }

//    asts.pop_back();

    int invincible = 60;

    ast astf1;
    astf1.vel = vel1;
    astf1.pos = pos1;
    astf1.points = ast1;
    astf1.invincible = invincible;

    ast astf2;
    astf2.vel = vel2;
    astf2.pos = pos2;
    astf2.points = ast2;
    astf2.invincible = invincible;

    if(astf1.points.size() > 3)
    {
        asts.push_back(astf1);
    }
    if(astf2.points.size() > 3)
    {
        asts.push_back(astf2);
    }

}

int main()
{
    Graphics g("Test", 1024, 768);

    ship player;

    ast Ast;

    Ast.points = {};

    for(double a = 0; a < 100; a += 3.1415/100)
    {
        Ast.points.push_back({50*cos(a),50*sin(a)});
    }

    vector<ast> asts{Ast};

    while (g.draw()) {

        player.update(g);
        player.draw(g);

        for(int i = 0; i < asts.size(); i++)
        {
            asts[i].draw(g);
            asts[i].update(g);
        }



        g.cout << colDet1(Ast, player);
        for(int i = 0; i < asts.size(); i++)
        {
            if(colDet1(asts[i],player) && asts[i].invincible < 0)
            {
                splitR(g, asts, i, player);
            }
        }
//        for (const Event& e : g.events()) {
//            g.cerr << e << endl;

//            switch (e.evtType) {
//            case EvtType::KeyPress:
//                break;
//            case EvtType::KeyRelease:
//                break;
//            case EvtType::MouseMove:
//                break;
//            case EvtType::MousePress:
//                break;
//            case EvtType::MouseRelease:
//                break;
//            default:
//                break;
//            }
//        }
    }

    return 0;
}


