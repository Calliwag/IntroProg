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
    double speed = 1.7;
    double botspeed = 1.4;
    Vec2d ballpos{200,200};
    Vec2d ballvel{0,0};
    int linel = 15;
    ballvel.x = 4;
    ballvel.y = (rand()%10)/10.0;
    int mult = rand()%2;
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
        g.cout << setw(33) << botscore <<"   : "<< setw(3) << playscore;
        //double test = (playscore - botscore)/10;
        //ballvel.x = 4 + test;
        int playertop = player.y+linel;
        int playerbot = player.y-linel;
        int bottop = bot.y+linel;
        int botbot = bot.y-linel;
        g.line({player.x, playertop},{player.x, playerbot});
        g.line({bot.x, bottop},{bot.x, botbot});
        g.ellipse(ballpos, 3, 3);
        if(g.isKeyPressed(Key::Up) && !(playertop <= 0))
        {
            player.y -= speed;
        }
        if(g.isKeyPressed(Key::Down) && !(playerbot >= 400))
        {
            player.y += speed;
        }
        if(ballpos.y > bot.y)
        {
            bot.y += botspeed;
        }
        if(ballpos.y < bot.y)
        {
            bot.y -= botspeed;
        }

        if(ballpos.x <= 3)
        {
            playscore++;
            ballpos = {200,200};
            player.y = 200;
            bot.y = 200;
            ballvel.y = (rand()%10)/10.0;
            int mult = rand()%2;
            if(mult == 0)
            {
                ballvel.y -= 1;
            }
            if(mult == 1)
            {
                ballvel.y += 1;
            }
            freezecount = 0;
        }
        if(ballpos.x >= 397)
        {
            botscore++;
            ballpos = {200,200};
            player.y = 200;
            bot.y = 200;
            ballvel.y = (rand()%10)/10.0;
            int mult = rand()%2;
            if(mult == 0)
            {
                ballvel.y -= 1;
            }
            if(mult == 1)
            {
                ballvel.y += 1;
            }
            freezecount = 0;
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
        if(freezecount >75)
        {
            ballpos += ballvel;
        }
        else
        {
            freezecount ++;
            g.line(ballpos,ballpos+5*ballvel);
        }

    }

    return 0;
}

