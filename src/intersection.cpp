#include "intersection.h"

using traffic_object::object_type;

intersection::intersection::intersection()
{
    _object_type = object_type::OBJECT_INTERSECTION;
}

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