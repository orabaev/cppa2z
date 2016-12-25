#include <catch.hpp>

using namespace std;

static int static_i = 0;

TEST_CASE( "[]", "[std] [modern] [lambda]" ) {
    
    SECTION( "default capture nothing minimal lambda called directly" ) {
        [] { static_i = 1; } ();

        REQUIRE( 1 == static_i);
    }

    SECTION( "lambda called through assigned variable" ) {
        auto func = [] { static_i = 2; };

        func();

        REQUIRE( 2 == static_i);
    }

    SECTION( "passing parameters" ) {
        auto is_even = [](int x) { return x % 2 == 0; };

        REQUIRE( is_even(10) );
        REQUIRE_FALSE( is_even(11) );
    }

}

TEST_CASE( "[=]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variables by value" ) {
        const int x = 4;
        const int y = 3;

        auto add_x_y = [=] { return x + y; };

        const int ret = add_x_y();

        REQUIRE( 7 == ret );
    }

}

TEST_CASE( "lambda.mutable", "[std] [modern] [lambda]" ) {

    SECTION( "modified captured by value local variables" ) {
        int x = 0;

        auto set_x = [=] () mutable { x = 10; return x; };

        const int ret = set_x();

        REQUIRE(  0 == x );
        REQUIRE( 10 == ret );
    }

}

TEST_CASE( "[&]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variables by reference" ) {
        int x = 3;
        int y = 4;

        auto reset = [&] { x = y = 0; };

        reset();

        REQUIRE( 0 == x );
        REQUIRE( 0 == y );
    }

}

TEST_CASE( "[&x, y]", "[std] [modern] [lambda]" ) {

    SECTION( "capture local variable x by reference and y by value" ) {
        int x = 0;
        int y = 7;

        auto x_assign_y = [&x, y] { x = y; };

        x_assign_y();

        REQUIRE( 7 == x );
    }

}
