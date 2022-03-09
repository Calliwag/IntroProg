#include <iostream>
#include <vector>
#include <cmath>

#pragma GCC diagnostic ignored "-Wsign-compare"

using namespace std;

template<typename T>
void printVector(vector<T> values)
{
    cout << "{ ";
    for (int i = 0; i < values.size(); i++)
    {
        cout << values[i] << (i < values.size()-1 ? ", " : " ");
    }
    cout <<"}"<< endl;
}

template<typename T>
void getVector(vector<T>& values)
{

    int i = 0;
    cout <<"Enter values:"<< endl;
    cout << endl;
    while(true)
    {
        int current;
        cin >> current;
        values.push_back(current);
        if(cin.peek() == '\n')
        {
            break;
        }
        i++;
    }
    cout << endl;
}

int main()
{



    return 0;
}
