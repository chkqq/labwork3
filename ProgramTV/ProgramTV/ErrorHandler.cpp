#include <iostream>
#include "ErrorHandler.h"

using namespace std;

void ShowError(ostream& out, const string& message)
{
    out << "Error: " << message << "\n";
}
