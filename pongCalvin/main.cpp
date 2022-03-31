#include <iostream>
#include "graphics.h"
#include <iomanip>

using namespace std;
using namespace mssm;

#pragma GCC diagnostic ignored "-Wsign-compare"

int main()
{
    srand(time(NULL));
    Graphics g("Test", 400, 400);
    Vec2d player{375,200};
    Vec2d bot{25,200};
    double speed = 1.5;
    double botspeed = 1.2;
    Vec2d ballpos{200,200};
    Vec2d ballvel{0,0};
    int linel = 15;
    ballvel.x = 4;
    ballvel.y = (rand()%10)/10.0;
    int mult = rand()%1;
    if(mult == 0)
    {
        ballvel.y -= 1;
    }
    if(mult == 1)
    {
        ballvel.y += 1;
    }
    int botscore = 0;
    int playscore = 0;
    int freezecount = 0;
    while (g.draw())
    {
        g.cout << setw(3) << botscore <<" : "<< setw(3) << playscore;
        int playertop = player.y+linel;
        int playerbot = player.y-linel;
        int bottop = bot.y+linel;
        int botbot = bot.y-linel;
        g.line({player.x, playertop},{player.x, playerbot});
        g.line({bot.x, bottop},{bot.x, botbot});
        g.ellipse(ballpos, 3, 3);
        if(g.isKeyPressed(Key::Up))
        {
            player.y -= speed;
        }
        if(g.isKeyPressed(Key::Down))
        {
            player.y += speed;
        }
        if(ballpos.y > botbot)
        {
            bot.y += botspeed;
        }
        if(ballpos.y < bottop)
        {
            bot.y -= botspeed;
        }

        if(ballpos.x <= 3)
        {
            playscore++;
            ballpos = {200,200};
            player.y = 200;
            bot.y = 200;
            ballvel.y = (rand()%20)/10.0 - 1;
        }
        if(ballpos.x >= 397)
        {
            botscore++;
            ballpos = {200,200};
            player.y = 200;
            bot.y = 200;
            ballvel.y = (rand()%20)/10.0 - 1;
        }
        if(ballpos.y <= 3)
        {
            ballvel.y *= -1;
        }
        if(ballpos.y >= 397)
        {
            ballvel.y *= -1;
        }
        if((ballpos.y >= playerbot && ballpos.y <= playertop) && (ballpos.x == player.x-3))
        {
            ballvel.x *= -1;
        }
        if((ballpos.y >= botbot && ballpos.y <= bottop) && (ballpos.x == bot.x+3))
        {
            ballvel.x *= -1;
        }
        if(freezecount >30)
        {
            ballpos += ballvel;
        }
        else
        {
            freezecount ++;
        }

    }

    return 0;
}

