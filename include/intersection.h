#pragma once

#include <memory>
#include <vector>
#include "traffic_light.h"
#include "traffic_object.h"
#include <thread>

using traffic_light::traffic_light_state;

namespace street
{
    class street;
}

namespace traffic_light
{
    class traffic_light;
}

namespace intersection
{
    class intersection : public traffic_object::traffic_object
    {
    public:
        intersection();
        ~intersection() = default;

        void setPosition(float x, float y)
        {
            _pos_x = x;
            _pos_y = y;
        }

        void add_street(std::shared_ptr<street::street>);
        void simulate();
        traffic_light_state get_current_light() { return _traffic_light.get_current_light(); }

    private:
        float _pos_x{}, _pos_y{};
        std::vector<std::shared_ptr<street::street>> _streets_ptrs{};
        traffic_light::traffic_light _traffic_light{};

        void process_vehicle_queue();
    };
}