#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

void displayDice(vector<int> dice)
{
    for (int i = 0; i < dice.size(); i++)
    {
        cout << " |" << dice[i] << "| ";
    }
    cout << endl;
}

void roll(vector<int>& dice, vector<bool> reroll = {true,true,true,true,true})
{
    for(int i = 0; i < dice.size(); i++)
    {
        if(reroll[i] == true)
        {
            dice[i] = rand()%6 + 1;
        }
    }
}

void reroller(vector<int>& dice)
{
    for(int i = 0; i < 2; i++)
    {
        vector<bool> reroll{false,false,false,false,false};
        bool toRoll;
        cout << "Would you like to reroll (type 1 for yes or 0 for no)?" << endl;
        cin >> toRoll;
        if(toRoll == false)
        {
            break;
        }
        cout << "What dice would you like to reroll or hold (type 0 for hold and 1 for reroll)?" << endl;
        for(int it = 0; it < 5; it++)
        {
            int current;
            cin >> current;
            if(current == 1)
            {
                reroll[it] = true;
            }
        }
        roll(dice, reroll);
        displayDice(dice);
    }
}

int scoreTop(vector<int> dice, int num)
{
    int score = 0;
    for(int i = 0; i < dice.size(); i++)
    {
        if(dice[i] == num)
        {
            score += num;
        }
    }
    return score;
}

int scoreSetOf(vector<int> dice, int goal)
{
    for(int i = 1; i <= 6; i++)
    {
        int count = 0;
        for(int it = 0; it < dice.size(); it++)
        {
            if(dice[it] == i)
            {
                count++;
            }
        }
        if(count >= goal)
        {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        }
    }
    return 0;
}

int smStr(vector<int> dice)
{
    if(dice[0]+1 == dice[1] && dice[1]+1 == dice[2] && dice[2]+1 == dice[3])
    {
        return 30;
    }
    else if(dice[1]+1 == dice[2] && dice[2]+1 == dice[3] && dice[3]+1 == dice[4])
    {
        return 30;
    }
    return 0;
}

int lgStr(vector<int> dice)
{
    if(dice[0]+1 == dice[1] && dice[1]+1 == dice[2] && dice[2]+1 == dice[3] && dice[3]+1 == dice[4])
    {
        return 40;
    }
    return 0;
}

int calculateScore(vector<int> dice, int rule)
{

    switch (rule)
    {
    case 1:
        return scoreTop(dice,1);

    case 2:
        return scoreTop(dice,2);

    case 3:
        return scoreTop(dice,3);

    case 4:
        return scoreTop(dice,4);

    case 5:
        return scoreTop(dice,5);

    case 6:
        return scoreTop(dice,6);

    case 7:
        return scoreSetOf(dice, 3);

    case 8:
        return scoreSetOf(dice, 4);

    case 9:
        return 0;

    case 10:
        return smStr(dice);

    case 11:
        return lgStr(dice);


    }
}

int main()
{
    srand(time(NULL));
    while(true)
    {
        vector<int> dice{1,2,3,4,5};
        roll(dice);
        displayDice(dice);
        cout << calculateScore(dice, 11) << endl;
        if(calculateScore(dice, 11) != 0)
        {
            break;
        }
    }
    //reroller(dice);



    return 0;
}
