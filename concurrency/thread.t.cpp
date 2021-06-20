#include <catch.hpp>
#include <thread>
#include <type_traits>
#include <atomic>
#include <chrono>

using namespace std;

static int global_i = 0;

void thread_function()
{
    global_i = 12;
}

void thread_function_with_ref_arg(int& i)
{
    i = 12;
}

TEST_CASE( "running", "[std] [modern] [concurrency]" ) {
    global_i = 0;

    SECTION( "function" ) 
    {
        thread t(thread_function);
        t.join();
        REQUIRE( global_i == 12 );
    }

    SECTION( "function with reference argument" ) 
    {
        int i = 0;
        thread t(thread_function_with_ref_arg, std::ref(i));
        t.join();
        REQUIRE( i == 12 );
    }

    SECTION( "lambda" ) 
    {
        int i = 0;
        auto lambda = [&] { i = 12; };
        thread t(lambda);
        t.join();
        REQUIRE( i == 12 );
    }

    SECTION( "class member function" ) 
    {
        struct A {
            int i = 0;
            void func() { i = 12; }
        };
        A a;
        thread t(&A::func, std::ref(a));
        t.join();
        REQUIRE( a.i == 12 );
    }
}

TEST_CASE( "traits", "[std] [modern] [concurrency]" ) {
    SECTION( "traits" ) 
    {
        static_assert( is_copy_constructible_v<thread> == false );
        static_assert( is_copy_assignable_v<thread>    == false );
        static_assert( is_move_constructible_v<thread> == true  );
        static_assert( is_move_assignable_v<thread>    == true  );
    }
}

TEST_CASE( "join", "[std] [modern] [concurrency]" ) {
    SECTION( "join" ) 
    {
        atomic<int> i = 0;
        auto increment_i = [&] { ++i; };

        vector<thread> threads;
        for (int j = 0; j < 10; ++j) threads.push_back(thread(increment_i));

        for (auto& t : threads)
        {
            REQUIRE( t.joinable() );
            REQUIRE_NOTHROW( t.join() );
        }

        REQUIRE( i == 10 );
    }
}

TEST_CASE( "detach", "[std] [modern] [concurrency]" ) {
    SECTION( "detach" ) 
    {
        atomic<int> i = 0;
        auto increment_i = [&] { ++i; };

        vector<thread> threads;
        for (int j = 0; j < 10; ++j) threads.push_back(thread(increment_i));

        for (auto& t : threads)
        {
            REQUIRE( t.joinable() );
            REQUIRE_NOTHROW( t.detach() );
            REQUIRE_FALSE( t.joinable() );
        }

        while ( i != 10)
        {
            using namespace chrono_literals;
            this_thread::sleep_for(10ms);
        }
    }
}