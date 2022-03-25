#include <iostream>
#include <iomanip>
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

int calculateScore(vector<int> dice, vector<int>& scores, int rule, int yahtzees)
    {
    sort(dice.begin(), dice.end());

    if(yahtzee(dice) == 50 && scores [11] == 50)
    {
        yahtzees++;
    }
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

int calculateScoreNoTrack(vector<int> dice, vector<int>& scores, int rule, int yahtzees)
    {
    sort(dice.begin(), dice.end());

    if(yahtzee(dice) == 50 && scores [11] == 50)
    {
        yahtzees++;
    }
    switch (rule)
    {
    case 1:
        if(scores[0] == -1)
        {
            return scoreTop(dice,1);
        }
        else
        {
            return -2;
        }
    case 2:
        if(scores[1] == -1)
        {
            return scoreTop(dice,2);
        }
        else
        {
            return -2;
        }
    case 3:
        if(scores[2] == -1)
        {
            return scoreTop(dice,3);
        }
        else
        {
            return -2;
        }
    case 4:
        if(scores[3] == -1)
        {
            return scoreTop(dice,4);
        }
        else
        {
            return -2;
        }
    case 5:
        if(scores[4] == -1)
        {
            return scoreTop(dice,5);
        }
        else
        {
            return -2;
        }
    case 6:
        if(scores[5] == -1)
        {
            return scoreTop(dice, 6);
        }
        else
        {
            return -2;
        }
    case 7:
        if(scores[6] == -1)
        {
            return scoreSetOf(dice, 3);
        }
        else
        {
            return -2;
        }
    case 8:
        if(scores[7] == -1)
        {
            return scoreSetOf(dice, 4);
        }
        else
        {
            return -2;
        }
    case 9:
        if(scores[8] == -1)
        {
            return fullHouse(dice);
        }
        else
        {
            return -2;
        }
    case 10:
        if(scores[9] == -1)
        {
            return smStr(dice);
        }
        else
        {
            return -2;
        }
    case 11:
        if(scores[10] == -1)
        {
            return lgStr(dice);
        }
        else
        {
            return -2;
        }
    case 12:
        if(scores[11] == -1)
        {
            return yahtzee(dice);
        }
        else
        {
            return -2;
        }
    case 13:
        if(scores[12] == -1)
        {
            return chance(dice);
        }
        else
        {
            return -2;
        }

    }
}

int calcScore(vector<int> scores, int yahtzee)
{
    int score = 0;
    score = scores[0] + scores[1] + scores[2] + scores[3] + scores[4] + scores[5];
    if(score >= 63)
    {
        score += 35;
    }
    score = score + scores[6] + scores[7] + scores[8] + scores[9] + scores[10] + scores[11] + scores[12];
    score = score + (yahtzee * 100);
    return score;
}

void scoreSheet(vector<int> scores)
{
    int sp = 15;
    cout<<"       Yahtzee Score Sheet"<< endl << endl;
    cout<< setw(sp) <<"Ones"<<" | "<<(scores[0] == -1 ? "-" : to_string(scores[0]))<< endl;
    cout<< setw(sp) <<"Twos"<<" | "<<(scores[1] == -1 ? "-" : to_string(scores[1]))<< endl;
    cout<< setw(sp) <<"Threes"<<" | "<<(scores[2] == -1 ? "-" : to_string(scores[2]))<< endl;
    cout<< setw(sp) <<"Fours"<<" | "<<(scores[3] == -1 ? "-" : to_string(scores[3]))<< endl;
    cout<< setw(sp) <<"Fives"<<" | "<<(scores[4] == -1 ? "-" : to_string(scores[4]))<< endl;
    cout<< setw(sp) <<"Sixes"<<" | "<<(scores[5] == -1 ? "-" : to_string(scores[5]))<< endl;
    cout<< setw(sp) <<"Three of a Kind"<<" | "<<(scores[6] == -1 ? "-" : to_string(scores[6]))<< endl;
    cout<< setw(sp) <<"Four of a Kind"<<" | "<<(scores[7] == -1 ? "-" : to_string(scores[7]))<< endl;
    cout<< setw(sp) <<"Full House"<<" | "<<(scores[8] == -1 ? "-" : to_string(scores[8]))<< endl;
    cout<< setw(sp) <<"Small Straight"<<" | "<<(scores[9] == -1 ? "-" : to_string(scores[9]))<< endl;
    cout<< setw(sp) <<"Large Straight"<<" | "<<(scores[10] == -1 ? "-" : to_string(scores[10]))<< endl;
    cout<< setw(sp) <<"Yahtzee"<<" | "<<(scores[11] == -1 ? "-" : to_string(scores[11]))<< endl;
    cout<< setw(sp) <<"Chance"<<" | "<<(scores[12] == -1 ? "-" : to_string(scores[12]))<< endl << endl;
}

int main()
{
    vector<int> scores{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int yahtzee = 0;
    srand(time(NULL));
    cout << "Rules:" << endl <<"1 : Ones"<< endl <<"2 : Twos"<< endl <<"3 : Threes"<< endl <<"4 : Fours"<< endl <<"5 : Fives"<< endl <<"6 : Sixes"<< endl <<"7 : Three of a Kind"<< endl <<"8 : Four of a Kind"<< endl <<"9 : Full House"<< endl <<"10 : Small Straight"<< endl <<"11 : Large Straight"<< endl <<"12 : Yahtzee"<< endl <<"13 : Chance"<< endl;
    for(int i = 0; i < 13; i ++)
    {
        vector<int> dice{0,0,0,0,0};
        roll(dice);
        displayDice(dice);
        reroller(dice);
        int t = 1;
        while(t == 1)
        {
            cout <<"What rule would you like to use?"<< endl;
            int rule;
            cin >> rule;
            if(calculateScoreNoTrack(dice, scores, rule, yahtzee) != -2)
            {
                calculateScore(dice, scores, rule, yahtzee);
                scoreSheet(scores);
                t--;
            }
            else
            {
                cout <<"Rule already used!"<< endl;
            }
        }
    }
    cout <<"Your final score is "<< calcScore(scores, yahtzee) << endl;


    return 0;
}
