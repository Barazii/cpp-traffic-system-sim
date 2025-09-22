#pragma once

#include "traffic_object.h"
#include <semaphore>
#ifdef TESTING
#include <atomic>
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

#ifdef TESTING
    void stop_simulation_for_test();
    void release_semaphore_for_test();
#endif

    private:
        traffic_light_state current_light{traffic_light_state::RED};
        void switch_traffic_lights();
    std::binary_semaphore green_semaphore{0};
#ifdef TESTING
    std::atomic<bool> stop{false};
#endif
    };
}