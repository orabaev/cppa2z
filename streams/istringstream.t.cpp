#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "istringstream.ctor", "[std] [istringstream]" ) {

    SECTION( "istringstream is always opened in ios_base::in mode" ) {
        istringstream sin1;
        REQUIRE( 0 == sin1.tellg() );

        istringstream sin2{"Hello C++", ios_base::in};
        REQUIRE( 0 == sin2.tellg() );

        istringstream sin3{"Hello C++", ios_base::in | ios_base::ate};
        REQUIRE( 0 == sin3.tellg() );
    }
 
}

TEST_CASE( "istringstream.opearator=", "[std] [istringstream]" ) {

    SECTION( "operator=" ) {
        istringstream lin{"Original"};
        istringstream rin{"Moved from"};

        lin = move(rin);

        REQUIRE ( "Moved from" == lin.str() );
    }

}

TEST_CASE( "istringstream.swap", "[std] [istringstream]" ) {

    SECTION( "swap" ) {
        istringstream sin1{"sin1"};
        istringstream sin2{"sin2"};

        sin1.swap(sin2);

        REQUIRE ( "sin2" == sin1.str() );
        REQUIRE ( "sin1" == sin2.str() );
    }

}

TEST_CASE( "istringstream.rdbuf", "[std] [istringstream]" ) {

    SECTION( "rdbuf" ) {
        istringstream sin{"sin1"};

        REQUIRE ( nullptr != sin.rdbuf() );
    }

}

TEST_CASE( "istringstream.str", "[std] [istringstream]" ) {

    SECTION( "get/set str" ) {
        istringstream sin{"Hello C++"};
        REQUIRE ( "Hello C++" == sin.str() );

        sin.str("Hello Again");
        REQUIRE ( "Hello Again" == sin.str() );
    }

    SECTION( "set str after reading " ) {
        istringstream sin{"ABC 123"};

        string s;
        sin >> s;

        REQUIRE ( "ABC" == s );


        sin.str("EFG");
        sin >> s;

        REQUIRE ( "EFG" == s );
    }
    
}
