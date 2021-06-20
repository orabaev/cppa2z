#include <catch.hpp>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

TEST_CASE( "lock_guard", "[std] [modern] [concurrency]" ) {
    SECTION( "lock_guard" ) 
    {
        int i = 0;
        mutex mtx;

        auto lambda = [&] { 
            lock_guard lock(mtx);
            ++i; 
        };

        thread t1(lambda);
        thread t2(lambda);
        t1.join();
        t2.join();

        REQUIRE( i == 2 );
    }
}

TEST_CASE( "scoped_lock", "[std] [modern] [concurrency]" ) {
    SECTION( "lock multiple mutexes avoid deadlocks" ) 
    {
        int x = 0;

        auto lambda = [&](mutex& m1, mutex& m2) { 
            for (int i = 0; i < 10000; ++i)
            {
                scoped_lock lock(m1, m2);
                using namespace chrono_literals;
                this_thread::sleep_for(10us);
                ++x; 
            }
        };

        mutex mtx1;
        mutex mtx2;
        thread t1(lambda, std::ref(mtx1), std::ref(mtx2));
        thread t2(lambda, std::ref(mtx2), std::ref(mtx1));
        t1.join();
        t2.join();

        REQUIRE( x == 20000 );
    }
}