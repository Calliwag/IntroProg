#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>

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

int fullHouse(vector<int> dice)
{
    if(dice[0] == dice[1] && dice[2] == dice[3] && dice[3] == dice[4])
    {
        return 25;
    }
    else if(dice[0] == dice[1] && dice[1] == dice[2] && dice[3] == dice[4])
    {
        return 25;
    }

    return 0;
}

void redundancy(vector<int>& list)
{
    sort(list.begin(), list.end());

    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == list[i+1])
        {
            list[i+1] = -1;
            sort(list.begin(), list.end());
        }
    }
}

int smStr(vector<int> dice)
{
    redundancy(dice);
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

int yahtzee(vector<int> dice)
{
    if(dice[0] == dice[1] && dice[1] == dice[2] && dice[2] == dice[3] && dice[3] == dice[4])
    {
        return 50;
    }

    return 0;
}

int chance(vector<int> dice)
{
    return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
}

void trackScore(vector<int>& scores, int score, int rule)
{
    scores[rule-1] = score;
}

int calculateScore(vector<int> dice, vector<int>& scores, int rule)
    {
    sort(dice.begin(), dice.end());

    switch (rule)
    {
    case 1:
        if(scores[0] == -1)
        {
            trackScore(scores, scoreTop(dice,1), 1);
            return scoreTop(dice,1);
        }
    case 2:
        if(scores[1] == -1)
        {
            trackScore(scores, scoreTop(dice,2), rule);
            return scoreTop(dice,2);
        }
    case 3:
        if(scores[2] == -1)
        {
            trackScore(scores, scoreTop(dice,3), rule);
            return scoreTop(dice,3);
        }
    case 4:
        if(scores[3] == -1)
        {
            trackScore(scores, scoreTop(dice,4), rule);
            return scoreTop(dice,4);
        }
    case 5:
        if(scores[4] == -1)
        {
            trackScore(scores, scoreTop(dice,5), rule);
            return scoreTop(dice,5);
        }
    case 6:
        if(scores[5] == -1)
        {
            trackScore(scores, scoreTop(dice,6), rule);
            return scoreTop(dice, 6);
        }
    case 7:
        if(scores[6] == -1)
        {
            trackScore(scores, scoreSetOf(dice, 3), rule);
            return scoreSetOf(dice, 3);
        }
    case 8:
        if(scores[7] == -1)
        {
            trackScore(scores, scoreSetOf(dice, 4), rule);
            return scoreSetOf(dice, 4);
        }
    case 9:
        if(scores[8] == -1)
        {
            trackScore(scores, fullHouse(dice), rule);
            return fullHouse(dice);
        }
    case 10:
        if(scores[9] == -1)
        {
            trackScore(scores, smStr(dice), rule);
            return smStr(dice);
        }
    case 11:
        if(scores[10] == -1)
        {
            trackScore(scores, lgStr(dice), rule);
            return lgStr(dice);
        }
    case 12:
        if(scores[11] == -1)
        {
            trackScore(scores, yahtzee(dice), rule);
            return yahtzee(dice);
        }
    case 13:
        if(scores[12] == -1)
        {
            trackScore(scores, chance(dice), rule);
            return chance(dice);
        }

    }

    return -2;
}

int main()
{
    vector<int> scores{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    srand(time(NULL));
//    cout << "1 2 3 4 5" << endl;
//    cout << calculateScore({1,2,3,4,5}, scores, 10) << endl;
//    cout << "5 4 3 2 1" << endl;
//    cout << calculateScore({5,4,3,2,1}, scores, 10) << endl;
//    cout << "1 1 1 1 1" << endl;
//    cout << calculateScore({1,1,1,1,1}, scores, 10) << endl;
//    cout << "2 3 3 4 5" << endl;
//    cout << calculateScore({2,3,3,4,5}, scores, 10) << endl;
//    cout << "5 3 4 2 3" << endl;
//    cout << calculateScore({5,3,4,2,3}, scores, 10) << endl;

    for(int i = 0; i < 13; i ++)
    {
        vector<int> dice{0,0,0,0,0};
        roll(dice);
        cout << calculateScore(dice, scores, i+1) << endl;
    }


    return 0;
}
