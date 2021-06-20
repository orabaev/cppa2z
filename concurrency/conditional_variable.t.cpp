#include <catch.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

TEST_CASE( "wait-notify_one", "[std] [modern] [concurrency]" ) {
    SECTION( "wait-notify_one" ) 
    {
        condition_variable cv;
        mutex m;
        bool ready = false;
        bool reader_is_done = false;

        auto read = [&] () {
            unique_lock<std::mutex> lock(m);
            cv.wait(lock, [&]{return ready;}); 
            reader_is_done = true;
        };
        thread reader(read);

        this_thread::yield();
        REQUIRE_FALSE( ready );
        REQUIRE_FALSE( reader_is_done );

        auto write = [&] () {
            lock_guard lock(m);
            ready = true;
            cv.notify_one();
        };
        thread writer(write);

        reader.join();
        writer.join();

        REQUIRE( ready );
        REQUIRE( reader_is_done );
    }
}
