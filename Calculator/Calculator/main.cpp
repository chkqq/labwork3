#include <iostream>
#include "calculator.h"
#include "CalculatorConsoleHandler.h"

using namespace std;

int main() 
{
    Calculator calc;
    cout << "Type 'help' for available commands." << endl;
    while (true) 
    {
        cout << "> ";
        if (!ExecuteCommand())
        {
            break;
        }
    }

    return 0;
}
