#pragma once

#include <memory>
#include <vector>
#include "traffic_light.h"
#include "traffic_object.h"
#include <thread>
#include <future>

using traffic_light::traffic_light_state;

namespace intersection
{
    class intersection : public traffic_object::traffic_object
    {
    public:
        intersection();
        ~intersection() = default;

        void add_street(std::shared_ptr<street::street>);
        void simulate();
        traffic_light_state get_current_light();
        void add_vehicle_to_queue(std::shared_ptr<vehicle::vehicle>);
        std::vector<std::shared_ptr<street::street>> look_street_options(std::shared_ptr<street::street>);
        void notify_vehicle_leave();

    private:
        std::vector<std::shared_ptr<street::street>> streets_ptrs{};
        traffic_light::traffic_light traffic_light{};
        bool is_blocked{};
        std::mutex mutex{};

        class waiting_vehicles_queue
        {
        public:
            size_t get_size();
            void permit_next_entry();
            void add_vehicle_to_queue(std::shared_ptr<vehicle::vehicle>, std::promise<void> &&);

        private:
            std::vector<std::shared_ptr<vehicle::vehicle>> vehicles{};
            std::vector<std::promise<void>> promises{};
            std::mutex mutex{};
        };

        waiting_vehicles_queue waiting_vehicles{};
        void process_vehicle_queue();
    };
}