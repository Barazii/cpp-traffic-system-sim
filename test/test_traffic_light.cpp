#include <boost/test/unit_test.hpp>
#include "traffic_light.h"
#include <atomic>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

BOOST_AUTO_TEST_SUITE(test_traffic_light)

// Verify initial state is RED
BOOST_AUTO_TEST_CASE(initial_state_is_red)
{
    traffic_light::traffic_light tl;
    BOOST_CHECK(traffic_light::traffic_light_state::RED == tl.get_current_light());
}

// Verify wait_for_green blocks until semaphore is released
BOOST_AUTO_TEST_CASE(wait_for_green_blocks_and_unblocks)
{
    traffic_light::traffic_light tl;
    std::atomic<bool> unblocked{false};

    std::thread waiter([&]() {
        tl.wait_for_green();
        unblocked.store(true, std::memory_order_release);
    });

    // Give the waiter a moment to start and block
    std::this_thread::sleep_for(100ms);
    BOOST_CHECK(unblocked.load(std::memory_order_acquire) == false);

    // Release the semaphore to allow the waiter to proceed
    tl.test_release_semaphore();

    waiter.join();
    BOOST_CHECK(unblocked.load(std::memory_order_acquire) == true);
}

BOOST_AUTO_TEST_SUITE_END()
