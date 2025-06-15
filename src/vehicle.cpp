#include "vehicle.h"

using traffic_object::object_type;

vehicle::vehicle::vehicle()
{
    _object_type = object_type::OBJECT_VEHICLE;
}

void vehicle::vehicle::simulate()
{
    _threads.emplace_back(std::thread(&vehicle::drive, this));
}

void vehicle::vehicle::drive() {}