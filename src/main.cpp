#include <vector>
#include <memory>
#include <algorithm>
#include "street.h"
#include <intersection.h>

void create_traffic_objects(std::vector<std::shared_ptr<street::street>> &streets_ptrs, std::vector<std::shared_ptr<intersection::intersection>> &intersections_ptrs)
{
    std::generate_n(std::back_inserter(intersections_ptrs), size_t(9),
                    []()
                    { return std::make_shared<intersection::intersection>(); });

    // manually set positions
    intersections_ptrs.at(0)->setPosition(385, 270);
    intersections_ptrs.at(1)->setPosition(1240, 80);
    intersections_ptrs.at(2)->setPosition(1625, 75);
    intersections_ptrs.at(3)->setPosition(2110, 75);
    intersections_ptrs.at(4)->setPosition(2840, 175);
    intersections_ptrs.at(5)->setPosition(3070, 680);
    intersections_ptrs.at(6)->setPosition(2800, 1400);
    intersections_ptrs.at(7)->setPosition(400, 1100);
    intersections_ptrs.at(8)->setPosition(1700, 900);

    std::generate_n(std::back_inserter(streets_ptrs), size_t(8), []()
                    { return std::make_shared<street::street>(); });

    std::for_each(streets_ptrs.begin(), streets_ptrs.end(),
                  [&intersections_ptrs, i = 0](std::shared_ptr<street::street> street_ptr) mutable
                  {
                      street_ptr->set_in_intersection(intersections_ptrs.at(i++));
                      street_ptr->set_out_intersection(intersections_ptrs.at(8));
                  });
}

int main()
{
    std::vector<std::shared_ptr<street::street>> streets_ptrs{};
    std::vector<std::shared_ptr<intersection::intersection>> intersections_ptrs{};

    create_traffic_objects(streets_ptrs, intersections_ptrs);
}