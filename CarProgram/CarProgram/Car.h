#ifndef CAR_H
#define CAR_H   
#include <iostream>
#include <string>

using namespace std;

class Car
{
public:
    Car();
    bool IsTurnedOn() const;
    string GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
private:
    bool engineOn;
    int gear;
    int speed;
};

#endif