#include "traffic_light.h"
#include <random>
#include <chrono>

traffic_light::traffic_light::traffic_light()
{
    _current_light = traffic_light_state::RED;
}

void traffic_light::traffic_light::simulate()
{
    _threads.emplace_back(std::thread(&traffic_light::traffic_light::_switch_traffic_lights, this));
}

void traffic_light::traffic_light::_switch_traffic_lights()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(4.0, 6.0);

    auto last_time = std::chrono::high_resolution_clock::now();
    auto cycle_duration = std::chrono::duration<float>(dis(gen));

    while (true)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_elapsed = current_time - last_time;

        if (time_elapsed >= cycle_duration)
        {
            _current_light = (_current_light == traffic_light_state::GREEN) ? traffic_light_state::RED : traffic_light_state::GREEN;

            if (_current_light == traffic_light_state::GREEN)
                _green_semaphore.release();

            last_time = current_time;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}