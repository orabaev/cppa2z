#include <catch.hpp>

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
        REQUIRE(  1 == 1_square );
        REQUIRE(  4 == 2_square );
        REQUIRE(  9 == 3_square );

        
        REQUIRE( Approx(5.29) == 2.3_square );
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
        REQUIRE( 1'000 == binary_thousand);

        const int octal_thousand = 0001'750;
        REQUIRE( 1'000 == octal_thousand );

        const int hex_thousand = 0x03'E8;
        REQUIRE( 1'000 == hex_thousand );
    }

}
