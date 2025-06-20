#include <algorithm>
#include "traffic_object.h"
#include "intersection.h"
#include "vehicle.h"
#include "street.h"

int traffic_object::traffic_object::_id_count = 0;

traffic_object::traffic_object::~traffic_object()
{
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &thread)
                  { 
            if(thread.joinable())
                thread.join(); });
}

void traffic_object::create_traffic_objects(std::vector<std::shared_ptr<street::street>> &streets_ptrs, std::vector<std::shared_ptr<intersection::intersection>> &intersections_ptrs, std::vector<std::shared_ptr<vehicle::vehicle>> &vehicles_ptrs)
{
    std::generate_n(std::back_inserter(intersections_ptrs), size_t(9), []()
                    { return std::make_shared<intersection::intersection>(); });
    // manually set positions
    intersections_ptrs.at(0)->set_position(385, 270);
    intersections_ptrs.at(1)->set_position(1240, 80);
    intersections_ptrs.at(2)->set_position(1625, 75);
    intersections_ptrs.at(3)->set_position(2110, 75);
    intersections_ptrs.at(4)->set_position(2840, 175);
    intersections_ptrs.at(5)->set_position(3070, 680);
    intersections_ptrs.at(6)->set_position(2800, 1400);
    intersections_ptrs.at(7)->set_position(400, 1100);
    intersections_ptrs.at(8)->set_position(1700, 900);

    std::generate_n(std::back_inserter(streets_ptrs), size_t(8), []()
                    { return std::make_shared<street::street>(); });
    std::for_each(streets_ptrs.begin(), streets_ptrs.end(),
                  [&intersections_ptrs, i = 0](std::shared_ptr<street::street> street_ptr) mutable
                  {
                      street_ptr->set_in_intersection(intersections_ptrs.at(i++));
                      street_ptr->set_out_intersection(intersections_ptrs.at(8));
                  });

    std::generate_n(std::back_inserter(vehicles_ptrs), size_t(6), []()
                    { return std::make_shared<vehicle::vehicle>(); });
    std::for_each(vehicles_ptrs.begin(), vehicles_ptrs.end(), [&intersections_ptrs, &streets_ptrs, i = 0](std::shared_ptr<vehicle::vehicle> vehicle_ptr) mutable
                  { vehicle_ptr->set_next_street(streets_ptrs.at(i++)); 
                    vehicle_ptr->set_next_intersection(intersections_ptrs.at(8)); });
}