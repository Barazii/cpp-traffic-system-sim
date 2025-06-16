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

void intersection::intersection::process_vehicle_queue()
{
    while (true)
    {
        if (_waiting_vehicles.get_size() and !_is_blocked)
        {
            this->_is_blocked = true;
            _waiting_vehicles.permit_next_entry();
        }
    }
}

size_t intersection::intersection::waiting_vehicles_queue::get_size()
{
    return _vehicles.size();
}

void intersection::intersection::waiting_vehicles_queue::permit_next_entry()
{
    std::vector<std::promise<void>>::iterator first_promise_it = _promises.begin();
    std::vector<std::shared_ptr<vehicle::vehicle>>::iterator first_vehicle_it = _vehicles.begin();
    first_promise_it->set_value();
    _vehicles.erase(first_vehicle_it);
    _promises.erase(first_promise_it);
}