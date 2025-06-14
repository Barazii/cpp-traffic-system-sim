#pragma once

#include <thread>
#include <vector>

namespace traffic_object
{
    class traffic_object
    {
    public:
        traffic_object() = default;
        ~traffic_object();

    protected:
        std::vector<std::thread> _threads{};
    };
}
