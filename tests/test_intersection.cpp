#include <boost/test/unit_test.hpp>
#include "traffic_object.h"
#include "intersection.h"
#include "street.h"
#include "vehicle.h"
#include <string>
#include <memory>

BOOST_AUTO_TEST_SUITE(test_intersection)

BOOST_AUTO_TEST_CASE(test_1)
{
#ifdef CXX20
    std::cout << "Testing C++20 semaphore path" << std::endl;
#else
    std::cout << "Testing condition variable path" << std::endl;
#endif
    intersection::intersection i{};
    BOOST_CHECK(i.test_add_vehicle_to_queue(std::make_shared<vehicle::vehicle>()) == true);
}

BOOST_AUTO_TEST_SUITE_END()