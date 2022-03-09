#include <iostream>
#include <vector>

#pragma GCC diagnostic ignored "-Wsign-compare"

using namespace std;

void printVector(vector<int> values)
{
    cout << "{ ";
    for (int i = 0; i < values.size(); i++)
    {
        if(i == values.size() -1)
        {
            cout <<values[i]<<" ";
        }
        else
        {
            cout <<values[i]<<", ";
        }
    }
    cout <<"}"<< endl;
}

void printVector(vector<string> values)
{
    cout << "{ ";
    for (int i = 0; i < values.size(); i++)
    {
        if(i == values.size() -1)
        {
            cout <<values[i]<<" ";
        }
        else
        {
            cout <<values[i]<<", ";
        }
    }
    cout <<"}"<< endl;
}

void printVector(vector<double> values)
{
    cout << "{ ";
    for (int i = 0; i < values.size(); i++)
    {
        if(i == values.size() -1)
        {
            cout <<values[i]<<" ";
        }
        else
        {
            cout <<values[i]<<", ";
        }
    }
    cout <<"}"<< endl;
}

vector<double> addOne(vector<double> values)
{
    for(int i = 0; i < values.size(); i++)
    {
        values[i]++;
    }
    return values;
}

int main()
{
    //vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
    //printVector(values);

    //values.push_back(10);
    //printVector(values);

    //values.resize(20);
    //printVector(values);

    //values.pop_back();
    //printVector(values);

    //values.erase(values.begin() + 9);
    //printVector(values);

    vector<double> values{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    printVector(values);
    printVector(addOne(values));


    return 0;
}
