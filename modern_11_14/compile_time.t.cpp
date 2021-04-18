#include <catch.hpp>
#include <limits>
#include <array>
#include <map>
#include <string>
#include <sstream>

using namespace std;

TEST_CASE( "static assertions", "[std] [modern] [compile-time]" ) {
    
    SECTION( "must be compile-time expression" ) {
        static_assert(100 == 100, "expected to be evaluated at compile-time");

        constexpr int i = 10;
        static_assert(i == 10, "expected to be evaluated at compile-time");
    }

}

TEST_CASE( "constexpr", "[std] [modern] [compile-time]" ) {
    
    SECTION( "same as const" ) {
        constexpr int val1 = 10;
        static_assert(val1 == 10, "expected to be evaluated at compile-time");
        
        const int val2 = 10;
        static_assert(val2 == 10, "expected to be evaluated at compile-time");
    }

    SECTION( "functions return value" ) {
        struct functions {
            constexpr static int sqr(int val) {
                return val * val;
            }
        }; 
         
        // compile-time
        static_assert(functions::sqr(10) == 100, "expected to be evaluated at compile-time");
        
        // run-time
        int x = 10;
        int y = functions::sqr(10); 
        REQUIRE( y == 100 );
    }

    SECTION( "use numeric limits as template arguments" ) {
         array<int, numeric_limits<unsigned short>::min()> arr;
    }

    SECTION( "constexpr constructor" ) {
        struct class_a {
            int x;

            constexpr class_a(int val): x(val) {} 
        }; 

        // compile-time
        constexpr class_a a1(10);
        static_assert(a1.x == 10, "expected to be evaluated at compile-time");

        // run-time
        int i = 10;
        class_a a2(i);
        REQUIRE( a2.x == 10 );
    }

    SECTION( "constexpr member function" ) {
        struct class_a {
            int x;

            constexpr class_a(int val): x(val) {} 
            constexpr int sqr_x() const { return x * x; } 
        }; 

        // compile-time
        constexpr class_a a(10);
        static_assert(a.sqr_x() == 100, "expected to be evaluated at compile-time");
        static_assert(class_a(10).sqr_x() == 100, "expected to be evaluated at compile-time");

        // run-time
        int i = 10;
        class_a a2(i);
        REQUIRE( a2.sqr_x() == 100 );
    }

}
