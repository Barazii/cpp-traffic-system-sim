#pragma once

#include <memory>
#include "traffic_object.h"
#ifdef TESTING
#include <atomic>
#endif

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

#ifdef TESTING
    void stop_simulation_for_test();
    void set_speed_for_test(float speed);
#endif

    private:
        std::shared_ptr<street::street> _current_street_ptr{};
        std::shared_ptr<intersection::intersection> _current_intersection_ptr{};
        float _pos_street{};
        float _speed{};

#ifdef TESTING
    std::atomic<bool> _stop{false};
#endif
    };
}