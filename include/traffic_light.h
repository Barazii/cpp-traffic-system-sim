#pragma once

#include "traffic_object.h"
#ifdef CXX20
#include <semaphore>
#endif

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
        traffic_light() = default;
        ~traffic_light() = default;

        void simulate();
        traffic_light_state get_current_light();
        void wait_for_green();

    private:
        traffic_light_state current_light{traffic_light_state::RED};
        void switch_traffic_lights();
#ifdef CXX20
        std::binary_semaphore green_semaphore{0};
#endif
    };
}