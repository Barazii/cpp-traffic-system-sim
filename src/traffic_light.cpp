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
#ifdef CXX20
    green_semaphore.acquire();
#else
    std::unique_lock<std::mutex> locker(mutex);
    condition.wait(locker, [this]
                   { return green_light; });
    green_light = false;
#endif
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
        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_elapsed = std::chrono::duration<float>(current_time - last_time).count();

        if (time_elapsed >= cycle_duration)
        {
            current_light = (current_light == traffic_light_state::GREEN) ? traffic_light_state::RED : traffic_light_state::GREEN;

            if (current_light == traffic_light_state::GREEN)
            {
#ifdef CXX20
                green_semaphore.release();
#else
                {
                    std::lock_guard<std::mutex> locker(mutex);
                    green_light = true;
                }
                condition.notify_one();
#endif
            }

            last_time = current_time;
        }
    }
}