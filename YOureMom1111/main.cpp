#include <iostream>
#include <vector>

using namespace std;

vector<int> getChange(double given, double owed)
{
    double change = given - owed;
    vector<int> changeVector{0, 0, 0, 0, 0, 0, 0};
    while(change > 0)
    {
        if(change >= 10)
        {
            changeVector[0]++;
            change -= 10;
        }
        else if(change >= 5)
        {
            changeVector[1]++;
            change -= 5;
        }
        else if(change >= 1)
        {
            changeVector[2]++;
            change -= 1;
        }
        else if(change >= 0.25)
        {
            changeVector[3]++;
            change -= 0.25;
        }
        else if(change >= 0.1)
        {
            changeVector[4]++;
            change -= 0.1;
        }
        else if(change >= 0.05)
        {
            changeVector[5]++;
            change -= 0.05;
        }
        else
        {
            changeVector[6]++;
            change -= 0.01;
        }
    }
    return changeVector;

}

int main()
{

    while(true)
    {
        cout << "How much does the product cost?" << endl;
        cout << endl;
        double x;
        cin >> x;
        cout << endl;

        cout << "How much was paid for the product?" << endl;
        cout << endl;
        double y;
        cin >> y;
        cout << endl;

        cout <<"Change:"<< endl;
        cout << endl;
        for(int i = 0; i < 7; i++)
        {
            cout << getChange(y, x)[i];
            if(i == 0)
            {
                cout <<" Ten"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 1)
            {
                cout <<" Five"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 2)
            {
                cout <<" One"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 3)
            {
                cout <<" Quarter"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 4)
            {
                cout <<" Dime"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 5)
            {
                cout <<" Nickel"<< ((getChange(y, x)[i] != 1)?"s":"") << endl;
            }
            else if(i == 6)
            {
                cout <<" Penn"<< ((getChange(y, x)[i] != 1)?"ies":"y") << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
