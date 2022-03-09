#include <iostream>

using namespace std;

//int main()
//{
//    while(true)
//    {
//        int x;
//        int iteration = 0;
//        cin >> x;
//        int startNum = x;
//        int highScore = startNum;
//        while(x > 1)
//        {
//            if (x % 2 == 0)
//            {
//                x = x / 2;
//            }
//            else
//            {
//                x = 3 * x + 1;
//            }
//            if (highScore < x)
//            {
//                highScore = x;
//            }
//            cout << x << endl;
//            iteration = iteration + 1;
//        }
//        cout << startNum << " took " << iteration << " iterations." << endl;
//        cout << "Highest Number: " << highScore << endl;
//        cout << " " << endl;
//    }
//    return 0;
//}

int main()
{
    while(true)
    {
        double x;
        double y;
        string operation;
        double ans;
        cout << "Enter your first number:" << endl;
        cin >> x;
        cout << "" << endl;
        cout << "Enter your second number:" << endl;
        cin >> y;
        cout << "" << endl;
        cout << "Enter you operation:" << endl;
        cin >> operation;

        if(operation == "*")
        {
            ans = x * y;
        }
        else if(operation == "/")
        {
            ans = x / y;
        }
        else if(operation == "+")
        {
            ans = x + y;
        }
        else if(operation == "*")
        {
            ans = x - y;
        }
        else
        {
            cout << "Sure thing buddy" << endl;
            break;
        }
        cout << x << operation << y << "=" << ans << endl;
    }
    return 0;
}

