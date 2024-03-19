#include <iostream>
#include <string>
#include "Car.h"

using namespace std;

Car::Car() : engineOn(false), gear(0), speed(0) {}

bool Car::IsTurnedOn() const 
{
    return engineOn;
}

string Car::GetDirection() const 
{
    if (speed == 0)
        return "standing still";
    else if (speed > 0 && gear > 0)
        return "forward";
    else
        return "backward";
}

int Car::GetSpeed() const 
{
    return abs(speed);
}

int Car::GetGear() const 
{
    return gear;
}

bool Car::TurnOnEngine() 
{
    if (!engineOn) {
        engineOn = true;
        gear = 0;
        return true;
    }
    return false;
}

bool Car::TurnOffEngine()
{
    if (engineOn && gear == 0 && speed == 0) 
    {
        engineOn = false;
        return true;
    }
    return false;
}

bool Car::SetGear(int gear)
{
    if (!engineOn)
        return false;
    if (gear < -1 || gear > 5)
        return false;
    if (gear == -1 && speed != 0)
        return false;
    if (gear == -1 && this->gear > 0)
        return false;
    if (gear != 0 && this->gear == -1 && speed != 0)
        return false;
    this->gear = gear;
    return true;
}

bool Car::SetSpeed(int speed)
{
    if (!engineOn)
        return false;
    if (gear == 0) 
    {
        if (this->speed < speed) 
        {
            return false;
        }
        else
        {
            this->speed = speed;
            return true;
        }
    }
    int minSpeed, maxSpeed;
    switch (gear) {
    case -1:
        minSpeed = 0;
        maxSpeed = 20;
        break;
    case 1:
        minSpeed = 0;
        maxSpeed = 30;
        break;
    case 2:
        minSpeed = 20;
        maxSpeed = 50;
        break;
    case 3:
        minSpeed = 30;
        maxSpeed = 60;
        break;
    case 4:
        minSpeed = 40;
        maxSpeed = 90;
        break;
    case 5:
        minSpeed = 50;
        maxSpeed = 150;
        break;
    default:
        return false;
    }
    if (speed < minSpeed || speed > maxSpeed)
    {
        return false;
    }
    this->speed = speed;
    return true;
}