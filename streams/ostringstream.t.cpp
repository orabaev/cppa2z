#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "ostringstream.ctor", "[std] [streams] [ostringstream]" ) {

    SECTION( "default ctor ios_base::out mode" ) {
        ostringstream sout;

        REQUIRE( 0 == sout.tellp() );

        sout << "ABC";
        REQUIRE( "ABC" == sout.str() );
    }

    SECTION( "ctor ios_base::out mode" ) {
        ostringstream sout(ios_base::out);

        REQUIRE( 0 == sout.tellp() );

        sout << "ABC";
        REQUIRE( "ABC" == sout.str() );
    }

    SECTION( "ctor with string" ) {
        ostringstream sout("ABC");

        REQUIRE( "ABC" == sout.str() );

        REQUIRE( 0 == sout.tellp() );

        sout << 'D';
        REQUIRE( "DBC" == sout.str() );
    }

    SECTION( "ctor with string and ios_base::out mode" ) {
        ostringstream sout("ABC", ios_base::out);

        REQUIRE( "ABC" == sout.str() );

        REQUIRE( 0 == sout.tellp() );

        sout << 'D';
        REQUIRE( "DBC" == sout.str() );
    }

    SECTION( "ctor with string ios_base::app mode" ) {
        ostringstream sout("ABC", ios_base::app);

        REQUIRE( "ABC" == sout.str() );

        REQUIRE( 3 == sout.tellp() );

        sout << 'D';
        REQUIRE( "ABCD" == sout.str() );
    }

}

TEST_CASE( "ostringstream.opearator=", "[std] [streams] [ostringstream]" ) {

    SECTION( "operator=" ) {
        ostringstream lout{"Original"};
        ostringstream rout{"Moved from"};

        lout = move(rout);

        REQUIRE ( "Moved from" == lout.str() );
    }

}

TEST_CASE( "ostringstream.swap", "[std] [streams] [ostringstream]" ) {

    SECTION( "member swap" ) {
        ostringstream sout1{"sout1"};
        ostringstream sout2{"sout2"};

        sout1.swap(sout2);

        REQUIRE ( "sout2" == sout1.str() );
        REQUIRE ( "sout1" == sout2.str() );
    }

    SECTION( "std::swap" ) {
        ostringstream sout1{"sout1"};
        ostringstream sout2{"sout2"};

        swap(sout1, sout2);

        REQUIRE ( "sout2" == sout1.str() );
        REQUIRE ( "sout1" == sout2.str() );
    }

}

TEST_CASE( "ostringstream.rdbuf", "[std] [streams] [ostringstream]" ) {

    SECTION( "rdbuf" ) {
        ostringstream sout{"sout"};

        REQUIRE ( nullptr != sout.rdbuf() );
    }

}

TEST_CASE( "ostringstream.str", "[std] [streams] [ostringstream]" ) {

    SECTION( "get/set str" ) {
        ostringstream sout{"ABC"};

        REQUIRE ( "ABC" == sout.str() );
        REQUIRE ( 0 == sout.tellp() );

        sout.str("123");

        REQUIRE ( "123" == sout.str() );
        REQUIRE ( 0 == sout.tellp() );
    }

    SECTION( "set str after writing " ) {
        ostringstream sout{"ABC"};

        REQUIRE ( 0 == sout.tellp() );
        sout << "DEF";

        REQUIRE ( "DEF" == sout.str() );
        REQUIRE ( 3 == sout.tellp() );

        sout.str("ABC");

        REQUIRE ( "ABC" == sout.str() );
        REQUIRE ( 0 == sout.tellp() );

        sout << "123";
        REQUIRE ( "123" == sout.str() );
    }
    
}
