#include <catch.hpp>
#include <thread>
#include <type_traits>
#include <atomic>
#include <future>
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

TEST_CASE( "propogate exception", "[std] [modern] [concurrency]" ) {
    SECTION( "propogate exception" ) 
    {
        auto lambda = [] () {
            throw runtime_error("Passing exception to main thread");
        };
        packaged_task<void(void)> task(lambda);
        auto fut = task.get_future();

        thread t(move(task));

        bool exception_happened = false;
        try
        {
            fut.get();
        }
        catch(const runtime_error& e)
        {
            exception_happened = true;
            REQUIRE( e.what() ==  "Passing exception to main thread"s );
        }
        
        t.join();
        REQUIRE( exception_happened );
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

        using namespace chrono_literals;
        this_thread::sleep_for(10ms);
        while ( i != 10)
        {
            this_thread::yield();
        }
    }
}

TEST_CASE( "get_id", "[std] [modern] [concurrency]" ) {
    SECTION( "get_id" ) 
    {
        auto do_nothing = []{};
        thread t(do_nothing);
        thread::id thread_id = t.get_id();
        thread::id not_a_thread; 
        REQUIRE( thread_id != not_a_thread );
        t.join();
    }
}

TEST_CASE( "native_handle", "[std] [modern] [concurrency]" ) {
    SECTION( "native_handle" ) 
    {
        auto do_nothing = []{};
        thread t(do_nothing);
        thread::native_handle_type handle = t.native_handle();
        thread::native_handle_type not_a_handle;
        REQUIRE( handle != not_a_handle );
        t.join();
    }
}

TEST_CASE( "this_thread", "[std] [modern] [concurrency]" ) {
    SECTION( "get_id" ) 
    {
        thread::id current_thread_id = this_thread::get_id();
        thread::id not_a_thread; 
        REQUIRE( current_thread_id != not_a_thread );
    }

    SECTION( "sleep_for" ) 
    {
        using namespace chrono_literals;
        this_thread::sleep_for(10us);
    }

    SECTION( "sleep_until" ) 
    {
        using namespace chrono_literals;
        using namespace chrono;
        auto start = steady_clock::now();
        auto wake_up = start + 10us;

        this_thread::sleep_until(wake_up);

        duration<double, std::micro> elapsed = steady_clock::now() - start;
        REQUIRE( elapsed.count() >= 10 );
    }

    SECTION( "yield" ) 
    {
        for (int i = 0; i < 1000; ++i) this_thread::yield();
    }
}
