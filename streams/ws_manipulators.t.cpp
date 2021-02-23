#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "skipws", "[std] [streams] [manipulators]" ) {
    
    SECTION( "skip white space characters from input" ) {
        istringstream sin{"A B C"};
        
        char a, b, c = '\0';        

        sin >> skipws >> a >> b >> c;

        REQUIRE( a == 'A' );
        REQUIRE( b == 'B' );
        REQUIRE( c == 'C' );
    }

}

TEST_CASE( "noskipws", "[std] [streams] [manipulators]" ) {
    
    SECTION( "do not skip white space characters from input" ) {
        istringstream sin{"A B C"};
        
        char a, b, c = '\0';        

        sin >> noskipws >> a >> b >> c;

        REQUIRE( a == 'A' );
        REQUIRE( b == ' ' );
        REQUIRE( c == 'B' );
    }

}

TEST_CASE( "ws", "[std] [streams] [manipulators]" ) {
    
    SECTION( "discards leading white space from input line" ) {
        istringstream sin{"    Hello C++\n   ws not discarded\n  ws discarded"};
        string str;

        getline(sin >> ws, str);  
        REQUIRE( str == "Hello C++" );

        getline(sin, str);  
        REQUIRE( str == "   ws not discarded" );


        getline(sin >> ws, str);  
        REQUIRE( str == "ws discarded" );
    }

}
