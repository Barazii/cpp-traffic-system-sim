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
    tl.release_semaphore_for_test();

    waiter.join();
    BOOST_CHECK(unblocked.load(std::memory_order_acquire) == true);
}

// Verify simulate eventually turns GREEN and unblocks waiting thread
BOOST_AUTO_TEST_CASE(simulate_eventually_turns_green_and_unblocks)
{
    traffic_light::traffic_light tl;
    tl.simulate();

    std::atomic<bool> unblocked{false};
    std::thread waiter([&]() {
        tl.wait_for_green();
        unblocked.store(true, std::memory_order_release);
    });

    auto const deadline = std::chrono::steady_clock::now() + 6s;
    while (!unblocked.load(std::memory_order_acquire) && std::chrono::steady_clock::now() < deadline)
        std::this_thread::sleep_for(20ms);

    waiter.join();
    BOOST_CHECK_MESSAGE(unblocked.load(std::memory_order_acquire), "simulate() did not turn GREEN within timeout");

    // Stop simulation thread (test hook) so test teardown is quick and clean
    tl.stop_simulation_for_test();
}

BOOST_AUTO_TEST_SUITE_END()
