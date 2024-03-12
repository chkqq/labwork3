#include <Windows.h>
#include "TV.h"

void SetLocale()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main()
{
    SetLocale();
    TVRun();
    return 0;
}