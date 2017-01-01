#include <catch.hpp>
#include <type_traits>
#include <map>
#include <string>
#include <vector>

using namespace std;

TEST_CASE( "rvalue references", "[std] [modern] [move symantics]" ) {
    
    SECTION( "named rvalue reference is an lvalue" ) {
        int&& named_rvalue_ref1 = 0;
        named_rvalue_ref1 = 1;

        static_assert( is_same<int&&, decltype(named_rvalue_ref1)>::value, "expected int&&" );
        static_assert( is_rvalue_reference<decltype(named_rvalue_ref1)>::value, "expected rvalue reference" );


        auto returns_value = []() -> int { return 0; };
        int&& named_rvalue_ref2 = returns_value();
        named_rvalue_ref2 = 1; 

        static_assert( is_same<int&&, decltype(named_rvalue_ref2)>::value, "expected int&&" );
        static_assert( is_rvalue_reference<decltype(named_rvalue_ref2)>::value, "expected rvalue reference" );
    }

    SECTION( "unnamed rvalue reference is an rvalue" ) {
        int x = 0;
        static_cast<int&&>(x); // unnamed
        // COMPILE ERROR static_cast<int&&>(x) = 1;

        move(x); // unnamed
        // COMPILE ERROR move(x) = 2;
    }

    SECTION( "only unnamed rvalue references can be passed as parameters to functions" ) {
        auto function_that_takes_rvalue_ref = [] (int&& x) { };

        int lvalue = 0;
        function_that_takes_rvalue_ref( static_cast<int&&>(lvalue) );
        function_that_takes_rvalue_ref( move(lvalue) );
        // COMPILE ERROR function_that_takes_rvalue_ref( lvalue );

        int& lvalue_ref = lvalue;
        function_that_takes_rvalue_ref( static_cast<int&&>(lvalue_ref) );
        function_that_takes_rvalue_ref( move(lvalue_ref) );
        // COMPILE ERROR function_that_takes_rvalue_ref( lvalue_ref );

        int&& named_rvalue_ref = 0;
        function_that_takes_rvalue_ref( static_cast<int&&>(named_rvalue_ref) );
        function_that_takes_rvalue_ref( move(named_rvalue_ref) );
        // COMPILE ERROR function_that_takes_rvalue_ref( named_rvalue_ref );
    }

}
