#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "resetiosflags", "[std] [streams] [manipulators]" ) {
    
    SECTION( "reset formating flags" ) {
        ostringstream sout;

        sout << hex << showbase << uppercase 
             << 255 
             << resetiosflags(ios::hex | ios::showbase | ios::uppercase)
             << ' '
             << 255;
        
        REQUIRE( "0XFF 255" == sout.str() ); 
    }

}

TEST_CASE( "setiosflags", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set formating flags" ) {
        ostringstream sout;

        sout << 255 
             << ' '
             << resetiosflags(ios::dec)
             << setiosflags(ios::hex | ios::showbase | ios::uppercase)
             << 255;
        
        REQUIRE( "255 0XFF" == sout.str() ); 
    }

}
