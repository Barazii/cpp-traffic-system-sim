#include "intersection.h"
#include <iostream>
#include "vehicle.h"
#include "street.h"
#include <algorithm>

using traffic_object::object_type;

traffic_light_state intersection::intersection::get_current_light() { return _traffic_light.get_current_light(); }

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
    std::lock_guard<std::mutex> locker(_mutex);
    _promises[0].set_value();
    _vehicles.erase(_vehicles.begin());
    _promises.erase(_promises.begin());
}

void intersection::intersection::waiting_vehicles_queue::add_vehicle_to_queue(std::shared_ptr<vehicle::vehicle> vehicle_ptr, std::promise<void> &&promise)
{
    std::lock_guard<std::mutex> locker(_mutex);
    _vehicles.push_back(vehicle_ptr);
    _promises.push_back(std::move(promise));
}

void intersection::intersection::add_vehicle_to_queue(std::shared_ptr<vehicle::vehicle> vehicle_ptr)
{
    std::unique_lock<std::mutex> locker(_mutex);
    std::cout << "Intersection #" << _id << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;
    locker.unlock();
    std::promise<void> promise{};
    std::future<void> future = promise.get_future();
    _waiting_vehicles.add_vehicle_to_queue(vehicle_ptr, std::move(promise));
    future.wait();
    locker.lock();
    std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle_ptr->get_id() << " is granted entry." << std::endl;
    locker.unlock();
    _traffic_light.wait_for_green();
    std::cout << "Current light: GREEN" << std::endl;
}

std::vector<std::shared_ptr<street::street>> intersection::intersection::look_street_options(std::shared_ptr<street::street> street_ptr)
{
    std::vector<std::shared_ptr<street::street>> street_options_ptrs{};
    std::unique_lock<std::mutex> locker(_mutex);
    std::copy_if(_streets_ptrs.begin(), _streets_ptrs.end(), std::back_inserter(street_options_ptrs), [street_ptr](const auto sp)
                 { return sp->get_id() != street_ptr->get_id(); });
    locker.unlock();
    return street_options_ptrs;
}

void intersection::intersection::notify_vehicle_leave()
{
    std::lock_guard<std::mutex> locker(_mutex);
    _is_blocked = false;
};
