#include <iostream>

using namespace std;

int main1()
{
    cout << "Hello World!" << endl;

    int x = 10;

    cout << x << endl;

    x = 2 * x;

    // operator is a symbol representing a function
    // binary operator takes two operands
    // arithmatic operators + - * / %  (% is a modulo operator)
    // = is the assignment operator
    // <<  is the stream output operator
    // " is a delimiter

    // int is for integers
    // double  is for real numbers
    // string is a string
    // type denotes possible values and operators

    // literal has a type and value

    // variable has a type, name, and value
    // can be an object

    // expression can be evaluated, and also has a type

    string firstName = "Calvin";
    string lastName = "Akom";

    cout << firstName << endl;

    cout << x << endl;

    return 0;
}

int main()
{
    while(true)
    {
        int x;
        int i = 0;
        cin >> x;
        int y = x;
        while(x != 1)
        {
            if (x % 2 == 0)
            {
                x = x / 2;
            }
            else
            {
                x = 3 * x + 1;
            }
            cout << x << endl;
            i = i + 1;
        }
        cout << y << " took " << i << " iterations." << endl;
    }
    return 0;
}
