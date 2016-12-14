#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "boolalpha noboolalpha", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "boolalpha" ) {
        stringstream ss;

        ss << boolalpha << true << ' ' << false;

        REQUIRE( "true false" == ss.str() );
    }

    SECTION( "noboolalpha" ) {
        stringstream ss;

        ss << noboolalpha << true << ' ' << false;

        REQUIRE( "1 0" == ss.str() );
    }

}

TEST_CASE( "showbase noshowbase", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "hex" ) {
        stringstream ss;

        ss << hex << showbase << 27 << " " << noshowbase << 27;

        REQUIRE( "0x1b 1b" == ss.str() );
    }

    SECTION( "oct" ) {
        stringstream ss;

        ss << oct << showbase << 27 << " " << noshowbase << 27;

        REQUIRE( "033 33" == ss.str() );
    }

    SECTION( "dec" ) {
        stringstream ss;

        ss << dec << showbase << 27 << " " << noshowbase << 27;

        REQUIRE( "27 27" == ss.str() );
    }

}

TEST_CASE( "showpoint noshowpoint", "[std] [ostream] [manipulators]" ) {
    
    SECTION( "floating-point with zeroes after decimal point" ) {
        stringstream ss;

        ss << showpoint << 27.0 << " " << noshowpoint << 27.0;

        REQUIRE( "27.0000 27" == ss.str() );
    }

    SECTION( "floating-point with non zeroes after decimal point" ) {
        stringstream ss;

        ss << showpoint << 27.12 << " " << noshowpoint << 27.12;

        REQUIRE( "27.1200 27.12" == ss.str() );
    }

}


