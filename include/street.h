#pragma once

#include <memory>
#include "traffic_object.h"

namespace street
{
    class street : public traffic_object::traffic_object, public std::enable_shared_from_this<street>
    {
    public:
        street() = default;
        ~street() = default;

        void set_in_intersection(std::shared_ptr<intersection::intersection>);
        std::shared_ptr<intersection::intersection> get_in_intersection();
        void set_out_intersection(std::shared_ptr<intersection::intersection>);
        std::shared_ptr<intersection::intersection> get_out_intersection();
        float get_length();

    private:
        std::shared_ptr<intersection::intersection> in_intersection_ptr{}, out_intersection_ptr{};
        float length{1000.0};
    };
}