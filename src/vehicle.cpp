#include "vehicle.h"
#include <iostream>
#include "street.h"
#include "intersection.h"
#include <cmath>
#include <random>

using traffic_object::object_type;
using traffic_object::position;

vehicle::vehicle::vehicle()
{
    _object_type = object_type::OBJECT_VEHICLE;
    _speed = 400; // m per s.
}

void vehicle::vehicle::simulate()
{
    _threads.emplace_back(std::thread(&vehicle::drive, this));
}

void vehicle::vehicle::set_next_street(std::shared_ptr<street::street> street_ptr) { _current_street_ptr = street_ptr; }
void vehicle::vehicle::set_next_intersection(std::shared_ptr<intersection::intersection> intersection_ptr)
{
    _current_intersection_ptr = intersection_ptr;
    _pos_street = 0.0;
}

void vehicle::vehicle::drive()
{
    std::cout << "Vehicle #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;

    bool entered_intersection = false;
    float cycle_duration = 1.0;
    auto last_time = std::chrono::system_clock::now();

    while (true
#ifdef TESTING
           && !_stop.load(std::memory_order_acquire)
#endif
    )
    {
        auto current_time = std::chrono::system_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();

        if (time_elapsed >= cycle_duration)
        {
            _pos_street += _speed * (time_elapsed / 1000.0);
            float completetion_rate = _pos_street / _current_street_ptr->get_length();

            std::shared_ptr<intersection::intersection> i{};
            i = (_current_intersection_ptr->get_id() == _current_street_ptr->get_in_intersection()->get_id()) ? _current_street_ptr->get_out_intersection() : _current_street_ptr->get_in_intersection();

            float xv{}, yv{}, dx{}, dy{}, l{};
            position position1, position2;
            position1 = i->get_position();
            position2 = _current_intersection_ptr->get_position();
            dx = position2.x - position1.x;
            dy = position2.y - position1.y;
            // l = sqrt(dx * dx + dy * dy);
            xv = position1.x + completetion_rate * dx;
            yv = position1.y + completetion_rate * dy;
            this->set_position(xv, yv);

            if (completetion_rate > 0.9 and !entered_intersection)
            {
                _current_intersection_ptr->add_vehicle_to_queue(shared_from_this());
                _speed /= 10.0;
                entered_intersection = true;
            }

            if (completetion_rate > 1.0 and entered_intersection)
            {
                auto street_options = _current_intersection_ptr->look_street_options(_current_street_ptr);
                std::shared_ptr<street::street> next_street_ptr{};

                if (street_options.size() > 0)
                {
                    std::random_device rd;
                    std::mt19937 eng(rd());
                    std::uniform_int_distribution<> dist(0, street_options.size() - 1);
                    next_street_ptr = street_options.at(dist(eng));
                }
                else
                    next_street_ptr = _current_street_ptr;

                std::shared_ptr<intersection::intersection> next_intersection_ptr;

                if (next_street_ptr->get_in_intersection()->get_id() == _current_intersection_ptr->get_id())
                    next_intersection_ptr = next_street_ptr->get_out_intersection();
                else
                    next_intersection_ptr = next_street_ptr->get_in_intersection();

                _current_intersection_ptr->notify_vehicle_leave();
                this->set_next_intersection(next_intersection_ptr);
                this->set_next_street(next_street_ptr);

                _speed *= 10.0;
                entered_intersection = false;
            }

            last_time = std::chrono::system_clock::now();
        }
    }
}

#ifdef TESTING
void vehicle::vehicle::stop_simulation_for_test()
{
    _stop.store(true, std::memory_order_release);
}

void vehicle::vehicle::set_speed_for_test(float speed)
{
    _speed = speed;
}
#endif