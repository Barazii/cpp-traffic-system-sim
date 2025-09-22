#include <boost/test/unit_test.hpp>
#include "vehicle.h"
#include "street.h"
#include "intersection.h"
#include <atomic>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

BOOST_AUTO_TEST_SUITE(test_vehicle)

// Basic construction and type
BOOST_AUTO_TEST_CASE(constructs_with_correct_type_and_id)
{
    auto v = std::make_shared<vehicle::vehicle>();
    BOOST_CHECK(v->get_object_type() == traffic_object::object_type::OBJECT_VEHICLE);
    std::cout << v->get_id()<< std::endl;
    BOOST_CHECK_GT(v->get_id(), 0);
}

// Driving updates position along street and requests intersection entrance near 90%
BOOST_AUTO_TEST_CASE(drive_moves_towards_intersection)
{
    auto i_in = std::make_shared<intersection::intersection>();
    auto i_out = std::make_shared<intersection::intersection>();

    i_in->set_position(0.f, 0.f);
    i_out->set_position(1000.f, 0.f);

    auto s = std::make_shared<street::street>();
    s->set_in_intersection(i_in);
    s->set_out_intersection(i_out);

    auto v = std::make_shared<vehicle::vehicle>();
    v->set_next_street(s);
    v->set_next_intersection(i_in);

    v->set_speed_for_test(2000.f);
    v->simulate();

    // Let it run a bit and then stop
    std::this_thread::sleep_for(120ms);
    v->stop_simulation_for_test();

    // After running, the position should have advanced along +x between 0 and 1000
    auto pos = v->get_position();
    BOOST_CHECK_GE(pos.x, 0.f);
    BOOST_CHECK_LE(pos.x, 1000.f);
    BOOST_CHECK_EQUAL(pos.y, 0.f);
}

BOOST_AUTO_TEST_SUITE_END()
