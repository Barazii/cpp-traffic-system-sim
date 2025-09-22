#include "traffic_light.h"
#include <random>
#include <chrono>
#include <iostream>

void traffic_light::traffic_light::simulate()
{
    _threads.emplace_back(std::thread(&traffic_light::traffic_light::switch_traffic_lights, this));
}

traffic_light::traffic_light_state traffic_light::traffic_light::get_current_light() { return current_light; }

void traffic_light::traffic_light::wait_for_green()
{
    green_semaphore.acquire();
}

void traffic_light::traffic_light::switch_traffic_lights()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(4.0, 6.0);

    auto last_time = std::chrono::high_resolution_clock::now();
    auto cycle_duration = std::chrono::duration<float>(dis(gen)).count();

    while (true)
    {
#ifdef TESTING
        if (stop.load(std::memory_order_acquire))
        {
            return;
        }
#endif
        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_elapsed = std::chrono::duration<float>(current_time - last_time).count();

        if (time_elapsed >= cycle_duration)
        {
            current_light = (current_light == traffic_light_state::GREEN) ? traffic_light_state::RED : traffic_light_state::GREEN;

            if (current_light == traffic_light_state::GREEN)
            {
                green_semaphore.release();
            }

            last_time = current_time;
        }
    }
}

void traffic_light::traffic_light::release_semaphore_for_test()
{
    green_semaphore.release();
}

#ifdef TESTING
void traffic_light::traffic_light::stop_simulation_for_test()
{
    stop.store(true, std::memory_order_release);
}
#endif
