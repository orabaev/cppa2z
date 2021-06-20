#include <catch.hpp>
#include <thread>

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