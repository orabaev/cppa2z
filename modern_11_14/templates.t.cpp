#include <catch.hpp>
#include <limits>
#include <array>
#include <map>
#include <string>
#include <sstream>

using namespace std;

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

namespace {

// sum
template<class T>
T sum(T v) {
      return v;
}

template<class T, class... Args>
T sum(T the_arg, Args... args) {
      return the_arg  + sum(args...);
}

// print
template<class T>
void print(ostream& out, const T& value) {
   out << value; 
}

template<class T, class... Args>
void print(ostream& out, T the_arg, Args... args) {
      out << the_arg << ' ';
      print(out, args...);
}

}

TEST_CASE( "variadic templates", "[std] [modern] [compile-time]" ) {
    
    SECTION( "use sum" ) {
        const int i = sum(1, 4, 5, 10);
        REQUIRE( 20 == i );
    }

    SECTION( "use print" ) {
        ostringstream sout;

        print(sout, "hello", 1, 'A');

        REQUIRE( "hello 1 A" == sout.str() );
    }

}
