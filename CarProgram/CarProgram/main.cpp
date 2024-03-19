#include <iostream>
#include <string>
#include <sstream>
#include "Car.h"

using namespace std;

void displayMenu();
bool turnOnEngine(Car& car);
bool turnOffEngine(Car& car);
void getCarInfo(const Car& car);

void PrintError(const string& error)
{
    cout << error << endl;
}

void PrintMissingParameterError(const string& parameter)
{
    PrintError("Missing parameter. Enter " + parameter + ".");
}

void PrintInvalidParameterError(const string& parameter)
{
    PrintError("Invalid " + parameter + ".");
}

void processCommand(Car& car, const string& command)
{
    istringstream iss(command);
    string cmd, param1, param2;
    iss >> cmd >> param1 >> param2;

    if (cmd.empty()) 
    {
        PrintError("Invalid command. Type 'help' for the list of commands.");
        return;
    }

    if (cmd == "turn_on_engine" || cmd == "1")
    {
        if (!turnOnEngine(car))
            PrintError("Engine is already on");
        else
            cout << "The engine was turn on" << endl;
    }
    else if (cmd == "turn_off_engine" || cmd == "2") 
    {
        if (!turnOffEngine(car))
            PrintError("Engine is already off");
        else
            cout << "The engine was turn off" << endl;
    }
    else if (cmd == "set_gear" || cmd == "3") 
    {
        if (param1.empty())
            PrintMissingParameterError("gear");
        int gear;
        if (!(istringstream(param1) >> gear))
        {
            PrintInvalidParameterError("gear setting");
            return;
        }
        if (car.SetGear(gear))
            cout << gear << "th gear was selected" << endl;
        else
            cout << "You can't select this gear" << endl;
    }
    else if (cmd == "set_speed" || cmd == "4") 
    {
        if (param1.empty())
            PrintMissingParameterError("speed");
        int speed;
        if (!(istringstream(param1) >> speed))
        {
            PrintInvalidParameterError("speed setting");
            return;
        }
        if (car.SetSpeed(speed))
            cout << "The car started moving at a speed " << speed << endl;
        else
            cout << "You can't select this speed" << endl;
    }
    else if (cmd == "get_car_info" || cmd == "5") 
    {
        getCarInfo(car);
    }
    else if (cmd == "exit" || cmd == "6")
    {
        cout << "Exiting..." << endl;
        exit(0);
    }
    else if (cmd == "help" || cmd == "0") 
    {
        displayMenu();
    }
    else {
        PrintError("Invalid command. Type 'help' or '0' for the list of commands.");
    }
}

void displayMenu() 
{
    cout << "Menu:" << endl;
    cout << "1. turn_on_engine" << endl;
    cout << "2. turn_off_engine" << endl;
    cout << "3. set_gear <gear>" << endl;
    cout << "4. set_speed <speed>" << endl;
    cout << "5. get_car_info" << endl;
    cout << "6. exit" << endl;
}

bool turnOnEngine(Car& car) 
{
    if (car.IsTurnedOn())
        return false;

    return car.TurnOnEngine();
}

bool turnOffEngine(Car& car)
{
    if ( car.GetGear() != 0 || car.GetSpeed() != 0)
        cout << "The car is moving so you can’t turn it off, stop and put it in neutral" << endl;
        return false;

    return car.TurnOffEngine();
}

void getCarInfo(const Car& car) 
{
    cout << "Car info:" << endl;
    cout << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << endl;
    cout << "Direction: " << car.GetDirection() << endl;
    cout << "Speed: " << car.GetSpeed() << endl;
    cout << "Gear: " << car.GetGear() << endl;
}

int main()
{
    Car car;
    cout << "Welcome to Car Control!\n";
    string command;
    while (true)
    {
        cout << "> ";
        getline(cin, command);
        processCommand(car, command);
    }
    return 0;
}
