#include <iostream>
#include "calculator.h"

using namespace std;

int main() 
{
    Calculator calc;

    cout << "Type 'help' for available commands." << endl;

    while (true) 
    {
        cout << "> ";
        if (!calc.ExecuteCommand()) {
            break;
        }
    }

    return 0;
}
