#pragma once

#include <memory>
#include "traffic_object.h"

namespace street
{
    class street : public traffic_object::traffic_object, public std::enable_shared_from_this<street>
    {
    public:
        street();
        ~street() = default;

        void set_in_intersection(std::shared_ptr<intersection::intersection>);
        std::shared_ptr<intersection::intersection> get_in_intersection() { return _in_intersection_ptr; }
        void set_out_intersection(std::shared_ptr<intersection::intersection>);
        std::shared_ptr<intersection::intersection> get_out_intersection() { return _out_intersection_ptr; }
        float get_length() { return _length; };

    private:
        std::shared_ptr<intersection::intersection> _in_intersection_ptr{}, _out_intersection_ptr{};
        float _length{};
    };
}