#pragma once

#include "traffic_object.h"
#include <semaphore>

namespace traffic_light
{
    enum class traffic_light_state
    {
        GREEN,
        RED
    };

    class traffic_light : public traffic_object::traffic_object
    {
    public:
        traffic_light();
        ~traffic_light() = default;

        void simulate();
        traffic_light_state get_current_light() { return _current_light; }

    private:
        traffic_light_state _current_light{};
        void _switch_traffic_lights();
        std::binary_semaphore _green_semaphore{0};
    };
}