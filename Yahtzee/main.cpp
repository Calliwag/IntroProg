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

void rollDice(vector<int>& dice)
{
    for(int i = 0; i < dice.size(); i++)
    {
        dice[i] = rand()%6 + 1;
    }
}

int main()
{
    srand(time(NULL));

    vector<int> dice{1,2,3,4,5};
    rollDice(dice);
    displayDice(dice);

    return 0;
}
