#pragma once

#include <memory>

namespace intersection
{
    class intersection;
}

namespace street
{
    class street : public std::enable_shared_from_this<street>
    {
    public:
        street() = default;
        ~street() = default;

        void set_in_intersection(std::shared_ptr<intersection::intersection>);
        void set_out_intersection(std::shared_ptr<intersection::intersection>);

    private:
        std::shared_ptr<intersection::intersection> _in_intersection_ptr{}, _out_intersection_ptr{};
    };
}