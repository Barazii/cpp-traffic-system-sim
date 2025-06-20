#include <vector>
#include <memory>
#include <algorithm>
#include "street.h"
#include "intersection.h"
#include "vehicle.h"
#include "graphics.h"

int main()
{
    std::vector<std::shared_ptr<street::street>> streets_ptrs{};
    std::vector<std::shared_ptr<intersection::intersection>> intersections_ptrs{};
    std::vector<std::shared_ptr<vehicle::vehicle>> vehicles_ptrs{};
    traffic_object::create_traffic_objects(streets_ptrs, intersections_ptrs, vehicles_ptrs);

    std::for_each(intersections_ptrs.begin(), intersections_ptrs.end(), [](std::shared_ptr<intersection::intersection> intersection_ptr)
                  { intersection_ptr->simulate(); });

    std::for_each(vehicles_ptrs.begin(), vehicles_ptrs.end(), [](std::shared_ptr<vehicle::vehicle> vehicle_ptr)
                  { vehicle_ptr->simulate(); });

    std::vector<std::shared_ptr<traffic_object::traffic_object>> traffic_objects_ptrs{};
    std::for_each(intersections_ptrs.begin(), intersections_ptrs.end(), [&traffic_objects_ptrs](std::shared_ptr<intersection::intersection> intersection_ptr)
                  { auto traffic_object_ptr = std::dynamic_pointer_cast<traffic_object::traffic_object>(intersection_ptr); 
                    traffic_objects_ptrs.push_back(traffic_object_ptr); });
    std::for_each(vehicles_ptrs.begin(), vehicles_ptrs.end(), [&traffic_objects_ptrs](std::shared_ptr<vehicle::vehicle> vehicles_ptr)
                  { auto traffic_object_ptr = std::dynamic_pointer_cast<traffic_object::traffic_object>(vehicles_ptr);
                    traffic_objects_ptrs.push_back(traffic_object_ptr); });

    graphics::graphics graphics{};
    graphics.set_background_filename(std::string("../paris.jpg"));
    graphics.simulate(std::move(traffic_objects_ptrs));
}