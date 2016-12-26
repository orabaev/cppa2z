#include <catch.hpp>

using namespace std;

static int static_i = 0;

TEST_CASE( "[]", "[std] [modern] [lambda]" ) {
    
    SECTION( "default, capture nothing, minimal lambda called directly" ) {
        [] { static_i = 1; } ();

        REQUIRE( 1 == static_i);
    }

    SECTION( "lambda called through assigned variable" ) {
        auto func = [] { static_i = 2; };

        func();

        REQUIRE( 2 == static_i);
    }

}

TEST_CASE( "[](int x)", "[std] [modern] [lambda]" ) {

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

TEST_CASE( "-> type", "[std] [modern] [lambda]" ) {

    SECTION( "explicitly return a particular type from lambda" ) {
        auto sqr = [] (int x) -> double { return x * x; };

        const auto value = sqr(4);

        REQUIRE( 16.0 == value );
    }

}

TEST_CASE( "[=, &x]", "[std] [modern] [lambda]" ) {

    SECTION( "capture x by reference the rest by value" ) {
        int x = 0;
        int y = 1;
        int z = 2;

        auto x_assign_y_plus_z = [=, &x] { x = y + z; };

        x_assign_y_plus_z();

        REQUIRE( 3 == x );
    }

}

TEST_CASE( "[&, x]", "[std] [modern] [lambda]" ) {

    SECTION( "capture x by value the rest by reference" ) {
        int x = 2;
        int y = 0;
        int z = 0;

        auto change_y_z = [&, x] { y = x * x; z = x * x * x; };

        change_y_z();

        REQUIRE( 4 == y );
        REQUIRE( 8 == z );
    }

}

TEST_CASE( "[this]", "[std] [modern] [lambda]" ) {

    class A {
    private:
        int m_x;

    public:
        A(int x): m_x(x) {}

        void reset_x_using_lambda() {
            auto lambda = [this] { m_x = 0; };

            lambda();
        }

        int get_x() { return m_x; }

    };

    SECTION( "use lambda from member function,  with the lambda having write access to object state" ) {
        A a{10};
        REQUIRE( 10 == a.get_x() );

        a.reset_x_using_lambda();
        REQUIRE( 0 == a.get_x() );
    }

}
