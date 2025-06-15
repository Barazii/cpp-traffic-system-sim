#include "vehicle.h"

void vehicle::vehicle::simulate()
{
    _threads.emplace_back(std::thread(&vehicle::drive, this));
}

void vehicle::vehicle::drive() {}