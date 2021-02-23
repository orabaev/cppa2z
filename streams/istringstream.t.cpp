#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "istringstream.ctor", "[std] [istringstream]" ) {

    SECTION( "istringstream is always opened in ios_base::in mode" ) {
        istringstream sin1;
        REQUIRE( sin1.tellg() == 0 );

        istringstream sin2{"Hello C++", ios_base::in};
        REQUIRE( sin2.tellg() == 0 );

        istringstream sin3{"Hello C++", ios_base::in | ios_base::ate};
        REQUIRE( sin3.tellg() == 0 );
    }
 
}

TEST_CASE( "istringstream.opearator=", "[std] [istringstream]" ) {

    SECTION( "operator=" ) {
        istringstream lin{"Original"};
        istringstream rin{"Moved from"};

        lin = move(rin);

        REQUIRE ( lin.str() == "Moved from" );
    }

}

TEST_CASE( "istringstream.swap", "[std] [istringstream]" ) {

    SECTION( "member swap" ) {
        istringstream sin1{"sin1"};
        istringstream sin2{"sin2"};

        sin1.swap(sin2);

        REQUIRE ( sin1.str() == "sin2" );
        REQUIRE ( sin2.str() == "sin1" );
    }

    SECTION( "std::swap" ) {
        istringstream sin1{"sin1"};
        istringstream sin2{"sin2"};

        swap(sin1, sin2);

        REQUIRE ( sin1.str() == "sin2" );
        REQUIRE ( sin2.str() == "sin1" );
    }

}

TEST_CASE( "istringstream.rdbuf", "[std] [istringstream]" ) {

    SECTION( "rdbuf" ) {
        istringstream sin{"sin1"};

        REQUIRE ( sin.rdbuf() != nullptr );
    }

}

TEST_CASE( "istringstream.str", "[std] [istringstream]" ) {

    SECTION( "get/set str" ) {
        istringstream sin{"Hello C++"};
        REQUIRE ( sin.str() == "Hello C++" );

        sin.str("Hello Again");
        REQUIRE ( sin.str() == "Hello Again" );
    }

    SECTION( "set str after reading " ) {
        istringstream sin{"ABC 123"};

        string s;
        sin >> s;

        REQUIRE ( s == "ABC" );


        sin.str("EFG");
        sin >> s;

        REQUIRE ( s == "EFG" );
    }
    
}
