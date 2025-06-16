#pragma once

namespace traffic_light
{
    enum class traffic_light_state
    {
        GREEN,
        RED
    };

    class traffic_light
    {
    public:
        traffic_light() = default;
        ~traffic_light() = default;

        void simulate();
        traffic_light_state get_current_light() { return _current_light; }

    private:
        traffic_light_state _current_light{};
    };
}