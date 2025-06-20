#pragma once

#include <memory>
#include "traffic_object.h"

namespace vehicle
{
    class vehicle : public traffic_object::traffic_object, public std::enable_shared_from_this<vehicle>
    {
    public:
        vehicle();
        ~vehicle() = default;

        void set_next_street(std::shared_ptr<street::street> street_ptr);
        void set_next_intersection(std::shared_ptr<intersection::intersection> intersection_ptr);
        void simulate();
        void drive();

    private:
        std::shared_ptr<street::street> _current_street_ptr{};
        std::shared_ptr<intersection::intersection> _current_intersection_ptr{};
        float _pos_street{};
        float _speed{};
    };
}