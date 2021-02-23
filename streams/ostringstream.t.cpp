#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "ostringstream.ctor", "[std] [streams] [ostringstream]" ) {

    SECTION( "default ctor ios_base::out mode" ) {
        ostringstream sout;

        REQUIRE( 0 == sout.tellp() );

        sout << "ABC";
        REQUIRE( sout.str() == "ABC" );
    }

    SECTION( "ctor ios_base::out mode" ) {
        ostringstream sout(ios_base::out);

        REQUIRE( 0 == sout.tellp() );

        sout << "ABC";
        REQUIRE( sout.str() == "ABC" );
    }

    SECTION( "ctor with string" ) {
        ostringstream sout("ABC");

        REQUIRE( sout.str() == "ABC" );

        REQUIRE( sout.tellp() == 0 );

        sout << 'D';
        REQUIRE( sout.str() == "DBC" );
    }

    SECTION( "ctor with string and ios_base::out mode" ) {
        ostringstream sout("ABC", ios_base::out);

        REQUIRE( sout.str() == "ABC" );

        REQUIRE( sout.tellp() == 0 );

        sout << 'D';
        REQUIRE( sout.str() == "DBC" );
    }

    SECTION( "ctor with string ios_base::app mode" ) {
        ostringstream sout("ABC", ios_base::app);

        REQUIRE( sout.str() == "ABC" );

        REQUIRE( sout.tellp() == 3 );

        sout << 'D';
        REQUIRE( sout.str() == "ABCD" );
    }

}

TEST_CASE( "ostringstream.opearator=", "[std] [streams] [ostringstream]" ) {

    SECTION( "operator=" ) {
        ostringstream lout{"Original"};
        ostringstream rout{"Moved from"};

        lout = move(rout);

        REQUIRE ( lout.str() == "Moved from" );
    }

}

TEST_CASE( "ostringstream.swap", "[std] [streams] [ostringstream]" ) {

    SECTION( "member swap" ) {
        ostringstream sout1{"sout1"};
        ostringstream sout2{"sout2"};

        sout1.swap(sout2);

        REQUIRE ( sout1.str() == "sout2" );
        REQUIRE ( sout2.str() == "sout1" );
    }

    SECTION( "std::swap" ) {
        ostringstream sout1{"sout1"};
        ostringstream sout2{"sout2"};

        swap(sout1, sout2);

        REQUIRE ( sout1.str() == "sout2" );
        REQUIRE ( sout2.str() == "sout1" );
    }

}

TEST_CASE( "ostringstream.rdbuf", "[std] [streams] [ostringstream]" ) {

    SECTION( "rdbuf" ) {
        ostringstream sout{"sout"};

        REQUIRE ( sout.rdbuf() != nullptr );
    }

}

TEST_CASE( "ostringstream.str", "[std] [streams] [ostringstream]" ) {

    SECTION( "get/set str" ) {
        ostringstream sout{"ABC"};

        REQUIRE ( sout.str() == "ABC" );
        REQUIRE ( sout.tellp() == 0 );

        sout.str("123");

        REQUIRE ( sout.str() == "123" );
        REQUIRE ( sout.tellp() == 0 );
    }

    SECTION( "set str after writing " ) {
        ostringstream sout{"ABC"};

        REQUIRE ( sout.tellp() == 0 );
        sout << "DEF";

        REQUIRE ( sout.str() == "DEF" );
        REQUIRE ( sout.tellp() == 3 );

        sout.str("ABC");

        REQUIRE ( sout.str() == "ABC" );
        REQUIRE ( sout.tellp() == 0 );

        sout << "123";
        REQUIRE ( sout.str() == "123" );
    }
    
}
