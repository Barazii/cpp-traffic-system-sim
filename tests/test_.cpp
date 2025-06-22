#include <boost/test/unit_test.hpp>
#include "traffic_object.h"

// struct ChatBotTestsFixture
// {
//     std::stringstream buffer;
//     std::streambuf *old;
//     ChatBotTestsFixture()
//     {
//         // Redirect cout to our stringstream
//         old = std::cout.rdbuf(buffer.rdbuf());
//     }
//     ~ChatBotTestsFixture()
//     {
//         // Restore cout
//         std::cout.rdbuf(old);
//     }
// };

BOOST_AUTO_TEST_SUITE(test_traffic_object)

BOOST_AUTO_TEST_CASE(test_1)
{
    std::vector<std::shared_ptr<street::street>> streets_ptrs{};
    std::vector<std::shared_ptr<intersection::intersection>> intersections_ptrs{};
    std::vector<std::shared_ptr<vehicle::vehicle>> vehicles_ptrs{};
    traffic_object::create_traffic_objects(streets_ptrs, intersections_ptrs, vehicles_ptrs);
    std::cout << streets_ptrs.size() << std::endl;
    BOOST_CHECK(intersections_ptrs.size() == 9);
    BOOST_CHECK(streets_ptrs.size() == 8);
    BOOST_CHECK(vehicles_ptrs.size() == 6);
}

BOOST_AUTO_TEST_SUITE_END()