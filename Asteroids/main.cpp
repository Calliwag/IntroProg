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
    int lives = 3;
    int invuln = 75;

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

    if(pos.x > g.width()+5)
    {
        pos.x = -5;
    }
    else if(pos.x < -5)
    {
        pos.x = g.width()+5;
    }

    if(pos.y > g.height()+5)
    {
        pos.y = -5;
    }
    else if(pos.y < -5)
    {
        pos.y = g.height()+5;
    }

    pos += vel;

    invuln --;
}

class ast
{
public:
    Vec2d pos{0,0};
    Vec2d vel{0,0};
    double width = 100;
    int protection = 100;

    void update(Graphics& g);
    void draw(Graphics& g);
};

void ast::update(Graphics& g)
{
    pos += vel;
    if(pos.x > g.width()+width/2)
    {
        pos.x = -width/2;
    }
    else if(pos.x < -width/2)
    {
        pos.x = g.width()+width/2;
    }

    if(pos.y > g.height()+width/2)
    {
        pos.y = -width/2;
    }
    else if(pos.y < -width/2)
    {
        pos.y = g.height()+width/2;
    }

    protection --;
}

void ast::draw(Graphics& g)
{
    g.ellipse(pos,width,width);
}

class boolet
{
public:
    Vec2d pos{0,0};
    Vec2d vel{0,0};
    double width = 1;
    int lifetime = 1000;

    void update(Graphics& g);
    void draw(Graphics& g);
};

void boolet::update(Graphics& g)
{
    pos += vel;
    if(pos.x > g.width()+width/2)
    {
        pos.x = -width/2;
    }
    else if(pos.x < -width/2)
    {
        pos.x = g.width()+width/2;
    }

    if(pos.y > g.height()+width/2)
    {
        pos.y = -width/2;
    }
    else if(pos.y < -width/2)
    {
        pos.y = g.height()+width/2;
    }
    lifetime --;
}

void boolet::draw(Graphics& g)
{
    g.ellipse(pos,width,width);
}

void createAst(Graphics& g, vector<ast>& asts, int n)
{
    for(int i = 0; i < n; i++)
    {
        Vec2d pos{g.randomInt(0,g.width()),g.randomInt(0,g.height())};
        Vec2d vel{g.randomDouble(-1,1),g.randomDouble(-1,1)};

        ast newAst;
        newAst.pos=pos;
        newAst.vel=vel;

        asts.push_back(newAst);
    }
}

void createBoolet(vector<boolet>& boolets, ship player)
{
    Vec2d pos{player.pos.x+10*cos(player.angle),player.pos.y+10*sin(player.angle)};
    Vec2d vel{cos(player.angle),sin(player.angle)};
    vel += player.vel;

    boolet newBoolet;
    newBoolet.pos=pos;
    newBoolet.vel=vel;

    boolets.push_back(newBoolet);
}

bool astast(ast ast1, ast ast2)
{
    if((ast1.pos-ast2.pos).magnitude() <= (ast1.width+ast2.width)/2)
    {
        return 1;
    }
    return 0;
}

bool shipast(ast ast, ship ship)
{
    if((ast.pos-ship.pos).magnitude() <= ast.width/2 && ship.invuln <= 0)
    {
        return 1;
    }
    return 0;
}

bool boolast(ast ast, boolet boolet)
{
    if((ast.pos-boolet.pos).magnitude() <= ast.width/2)
    {
        return 1;
    }
    return 0;
}

void split2(Graphics& g, vector<ast>& asts, int n)
{
    if(asts[n].width > 25 && asts[n].protection <= 0)
    {
        Vec2d vel1 = {g.randomDouble(-1,1),g.randomDouble(-1,1)};
        Vec2d vel2 = -1*vel1;
        vel1 += asts[n].vel;
        vel2 += asts[n].vel;

        int newWidth = asts[n].width/2;

        Vec2d pos = asts[n].pos;

        ast ast1;
        ast1.width=newWidth;
        ast1.vel=vel1;
        ast1.pos=pos;

        ast ast2;
        ast2.width=newWidth;
        ast2.vel=vel2;
        ast2.pos=pos;

        asts.erase(asts.begin() + n);
//        asts[n].width = 0;

        asts.push_back(ast1);
        asts.push_back(ast2);
    }
    else
    {
        asts.erase(asts.begin() + n);
//        asts[n].width = 0;
    }
}

void deleteBoolet(vector<boolet>& boolets, int n)
{
    boolets.erase(boolets.begin() + n);
}

void playerDeath(Graphics& g, ship& player, vector<ast>& asts )
{
    int count = -1;
    while(count != 0)
    {
        player.pos = {g.randomInt(0,g.width()),g.randomInt(0,g.height())};
        count = 0;
        for(int i = 0; i < asts.size(); i++)
        {
            if(shipast(asts[i], player))
            {
                count ++;
            }
        }
    }
    player.lives --;
    player.invuln = 75;
}

int main()
{
    Graphics g("Test", 1024, 768);

    ship player;

    vector<ast> asts;
    vector<boolet> boolets;

    createAst(g, asts, 10);

    int lifetime = 10;

    while (g.draw()) {

        player.update(g);
        player.draw(g);

        for(int i = 0; i < boolets.size(); i++)
        {
            boolets[i].update(g);
            boolets[i].draw(g);
        }

        for(int i = 0; i < asts.size(); i++)
        {
            asts[i].update(g);
            asts[i].draw(g);
        }

        if(g.isKeyPressed(' '))
        {
            if(lifetime <= 0)
            {
                createBoolet(boolets, player);
                lifetime = 10;
            }
            else
            {
                lifetime--;
            }
        }

        for(int a = 0; a < asts.size(); a++)
        {
            for(int b = 0; b < boolets.size(); b++)
            {
                if(boolast(asts[a],boolets[b]))
                {
                    split2(g, asts, a);
                    a--;
                    deleteBoolet(boolets, b);
                    b--;
                }
            }
        }

        for(int a = 0; a < asts.size(); a++)
        {
            if(shipast(asts[a], player))
            {
                playerDeath(g, player, asts);
                if(player.lives <= 0)
                {
                    return 0;
                }
            }
        }

        g.cout << "Lives: " << player.lives;

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


