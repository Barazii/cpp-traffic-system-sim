#include "intersection.h"

void intersection::intersection::add_street(std::shared_ptr<street::street> street_ptr)
{
    _streets_ptrs.push_back(street_ptr);
}

void intersection::intersection::simulate()
{
    _traffic_light.simulate();
    _threads.emplace_back(std::thread(&intersection::intersection::process_vehicle_queue, this));
}

void intersection::intersection::process_vehicle_queue() {}