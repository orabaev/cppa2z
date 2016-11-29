#include <catch.hpp>
#include <sstream>
#include <iostream>

using namespace std;

TEST_CASE( ">>", "[std] [iterator] [stream]" ) {
    
    SECTION( "read two int values from istream" ) {
        istringstream sin{"1 2"};

        int x = 0;

        REQUIRE( sin >> x );
        REQUIRE( 1 == x );

        REQUIRE( sin >> x );
        REQUIRE( 2 == x );

        REQUIRE_FALSE ( sin >> x );
        REQUIRE( sin.eof() );
    } 

    SECTION( "try read two int values from istream, first value is not an int" ) {
        istringstream sin{"a 2"};

        int x = 0;

        REQUIRE_FALSE( sin >> x );
        
        bool recoverable_error = sin.fail();
        REQUIRE( recoverable_error );

        // recover
        sin.clear();
        sin.ignore(1);

        REQUIRE( sin >> x );
        REQUIRE( 2 == x );

        REQUIRE_FALSE( sin >> x );
        REQUIRE( sin.eof() );
    }

}
