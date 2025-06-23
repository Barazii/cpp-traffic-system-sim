#include <boost/test/unit_test.hpp>
#include "graphics.h"
#include "traffic_object.h"
#include "intersection.h"
#include "vehicle.h"
#include <string>
#include <memory>

BOOST_AUTO_TEST_SUITE(test_graphics)

BOOST_AUTO_TEST_CASE(test_1)
{
    graphics::graphics g{};
    g.set_background_filename(std::string("../paris.jpg"));
    std::vector<std::shared_ptr<traffic_object::traffic_object>> traffic_objects_ptrs{};
    std::shared_ptr<intersection::intersection> intersection_ptr = std::make_shared<intersection::intersection>();
    std::shared_ptr<vehicle::vehicle> vehicle = std::make_shared<vehicle::vehicle>();
    traffic_objects_ptrs.push_back(std::dynamic_pointer_cast<traffic_object::traffic_object>(intersection_ptr));
    traffic_objects_ptrs.push_back(std::dynamic_pointer_cast<traffic_object::traffic_object>(vehicle));
    // g.simulate(std::move(traffic_objects_ptrs));
}

BOOST_AUTO_TEST_SUITE_END()