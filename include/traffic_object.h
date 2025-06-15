#pragma once

#include <thread>
#include <vector>

namespace traffic_object
{
    struct position
    {
        float x{}, y{};
    };

    enum class object_type
    {
        OBJECT_INTERSECTION,
        OBJECT_VEHICLE
    };

    class traffic_object
    {
    public:
        traffic_object() = default;
        ~traffic_object();

        position get_position() { return {_posx, _posy}; }

        object_type get_object_type() { return _object_type; }

    protected:
        std::vector<std::thread> _threads{};
        float _posx{}, _posy{};
        object_type _object_type{};
    };
}
