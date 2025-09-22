#include <boost/test/unit_test.hpp>
#include "traffic_object.h"
#include "intersection.h"
#include "vehicle.h"
#include "street.h"

BOOST_AUTO_TEST_SUITE(test_traffic_object)

// Test the create_traffic_objects function
BOOST_AUTO_TEST_CASE(test_create_traffic_objects)
{
    std::vector<std::shared_ptr<street::street>> streets_ptrs{};
    std::vector<std::shared_ptr<intersection::intersection>> intersections_ptrs{};
    std::vector<std::shared_ptr<vehicle::vehicle>> vehicles_ptrs{};
    traffic_object::create_traffic_objects(streets_ptrs, intersections_ptrs, vehicles_ptrs);
    
    BOOST_CHECK(intersections_ptrs.size() == 9);
    BOOST_CHECK(streets_ptrs.size() == 8);
    BOOST_CHECK(vehicles_ptrs.size() == 6);
}

// Test traffic_object position functionality
BOOST_AUTO_TEST_CASE(test_traffic_object_position)
{
    // Create a concrete derived object for testing
    auto intersection_obj = std::make_shared<intersection::intersection>();
    
    // Test initial position (should be 0, 0)
    traffic_object::position pos = intersection_obj->get_position();
    BOOST_CHECK_EQUAL(pos.x, 0.0f);
    BOOST_CHECK_EQUAL(pos.y, 0.0f);
    
    // Test setting position
    intersection_obj->set_position(100.5f, 200.7f);
    pos = intersection_obj->get_position();
    BOOST_CHECK_EQUAL(pos.x, 100.5f);
    BOOST_CHECK_EQUAL(pos.y, 200.7f);
}

// Test traffic_object ID functionality
BOOST_AUTO_TEST_CASE(test_traffic_object_id)
{
    auto intersection1 = std::make_shared<intersection::intersection>();
    auto intersection2 = std::make_shared<intersection::intersection>();
    auto vehicle_obj = std::make_shared<vehicle::vehicle>();
    
    // IDs should be unique
    int id1 = intersection1->get_id();
    int id2 = intersection2->get_id();
    int id3 = vehicle_obj->get_id();
    
    BOOST_CHECK_NE(id1, id2);
    BOOST_CHECK_NE(id1, id3);
    BOOST_CHECK_NE(id2, id3);
    
    // IDs should be positive
    BOOST_CHECK_GT(id1, 0);
    BOOST_CHECK_GT(id2, 0);
    BOOST_CHECK_GT(id3, 0);
}

// Test traffic_object type functionality
BOOST_AUTO_TEST_CASE(test_traffic_object_type)
{
    auto intersection_obj = std::make_shared<intersection::intersection>();
    auto vehicle_obj = std::make_shared<vehicle::vehicle>();
    
    // Check object types
    BOOST_CHECK(intersection_obj->get_object_type() == traffic_object::object_type::OBJECT_INTERSECTION);
    BOOST_CHECK(vehicle_obj->get_object_type() == traffic_object::object_type::OBJECT_VEHICLE);
}

// Test position struct
BOOST_AUTO_TEST_CASE(test_position_struct)
{
    traffic_object::position pos1;
    BOOST_CHECK_EQUAL(pos1.x, 0.0f);
    BOOST_CHECK_EQUAL(pos1.y, 0.0f);
    
    traffic_object::position pos2{150.5f, 250.7f};
    BOOST_CHECK_EQUAL(pos2.x, 150.5f);
    BOOST_CHECK_EQUAL(pos2.y, 250.7f);
}

BOOST_AUTO_TEST_SUITE_END()