#include <catch.hpp>
#include <chrono>

using namespace std;

TEST_CASE( "binary", "[std] [modern] [literals]" ) {
    
    SECTION( "use binary literals to conveniently represent bits" ) {
        const int switch_1 = 0b001;
        const int switch_2 = 0b010;
        const int switch_3 = 0b100;

        int switches = 0b101;

        bool is_switch_1_on = (switches & switch_1); 
        REQUIRE( is_switch_1_on );

        bool is_switch_2_on = (switches & switch_2); 
        REQUIRE_FALSE( is_switch_2_on );

        bool is_switch_3_on = (switches & switch_3); 
        REQUIRE( is_switch_3_on );
    }

}

// literal operator
long long operator "" _square(unsigned long long value) {
      return value * value;
}

long double operator "" _square(long double value) {
      return value * value;
}

TEST_CASE( "user-defined", "[std] [modern] [literals]" ) {
    
    SECTION( "use user defined literals to perform declarative auto conversions" ) {
        REQUIRE( 1_square == 1 );
        REQUIRE( 2_square == 4 );
        REQUIRE( 3_square == 9 );
        
        REQUIRE( 2.3_square == Approx(5.29) );
    }

}

TEST_CASE( "std-user-defined", "[std] [modern] [literals]" ) {
    
    SECTION( "chrono" ) {
        using namespace std::chrono_literals;
       
        auto day_in_hours           = 24h;
        auto day_in_minutes         = 1440min;
        auto day_in_seconds         = 86400s;
        auto day_in_milliseconds    = 86'400'000ms;
        auto day_in_microseconds    = 86'400'000'000us;
        auto day_in_nanoseconds     = 86'400'000'000'000ns;

        REQUIRE( day_in_minutes      == day_in_hours );
        REQUIRE( day_in_seconds      == day_in_hours );
        REQUIRE( day_in_milliseconds == day_in_hours );
        REQUIRE( day_in_microseconds == day_in_hours );
        REQUIRE( day_in_nanoseconds  == day_in_hours );
    }

}

TEST_CASE( "digit separators", "[std] [modern] [literals]" ) {
    
    SECTION( "use digit separators to visualy distinguish" ) {
        const int thousand = 1'000;
        const int million  = 1'000'000;
        const int billion  = 1'000'000'000;
        const int long_num = 1'234'567'890;
    }

    SECTION( "binary/octal/hex" ) {
        const int binary_thousand = 0b0011'1110'1000;
        REQUIRE( binary_thousand == 1'000 );

        const int octal_thousand = 0'1'750;
        REQUIRE( octal_thousand == 1'000 );

        const int hex_thousand = 0x03'E8;
        REQUIRE( hex_thousand == 1'000 );
    }

}
