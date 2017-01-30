#include <catch.hpp>
#include <limits>
#include <array>
#include <map>
#include <string>

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
        REQUIRE( 100 == y );
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

        // run-time
        int i = 10;
        class_a a2(i);
        REQUIRE( a2.sqr_x() == 100 );
    }

}

// using can be templated
template<class T>
using array_100 = array<T, 100>;

template<size_t  SIZE>
using int_array = array<int, SIZE>;

TEST_CASE( "template aliases", "[std] [modern] [compile-time]" ) {
    
    SECTION( "using is more clear than typedef" ) {
        using int32 = int;
        int32 i = numeric_limits<int32>::max();
    }

    SECTION( "using can be templated" ) {
        array_100<int>   int_arr;   
        static_assert( int_arr.size() == 100, "expected size to be 100" );

        array_100<short> short_arr;   
        static_assert( short_arr.size() == 100, "expected size to be 100" );

        int_array<10> arr1;
        static_assert( arr1.size() == 10, "expected size to be 10" );

        int_array<100> arr2;
        static_assert( arr2.size() == 100, "expected size to be 10" );
    }

}

TEST_CASE( "variadic templates", "[std] [modern] [compile-time]" ) {
    
    SECTION( "" ) {

    }

}
