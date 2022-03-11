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

void numScore(vector<int>& dice, int num)
{

}

int main()
{
    srand(time(0));
    vector<int> dice{1,2,3,4,5};
    roll(dice);
    displayDice(dice);
    //reroller(dice);



    return 0;
}
