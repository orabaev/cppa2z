#include <catch.hpp>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

TEST_CASE( "operator << ", "[std] [istream] [output]" ) {
    
    SECTION( "output bool" ) {
        ostringstream sout;
        bool value = true;
        sout << value << flush;
        
        REQUIRE( "1" == sout.str() ); 
    }

    SECTION( "output bool as string" ) {
        ostringstream sout;
        bool value = true;
        sout << boolalpha << value << flush;
        
        REQUIRE( "true" == sout.str() ); 
    }

    SECTION( "output int" ) {
        ostringstream sout;
        int value = 1234567;
        sout << value << flush;
        
        REQUIRE( "1234567" == sout.str() ); 
    }

    SECTION( "output double" ) {
        ostringstream sout;
        double value = 123.4567;
        sout << fixed << value << flush;
        
        REQUIRE( "123.456700" == sout.str() ); 
    }

    SECTION( "output pointer" ) {
        ostringstream sout;
        int value = 123;
        sout <<  &value << flush;
        
        REQUIRE( "0x" == sout.str().substr(0, 2) ); 
    }

    SECTION( "output nullptr" ) {
        ostringstream sout;
        void* ptr = nullptr;
        sout <<  ptr << flush;
        
        REQUIRE( "0x0" == sout.str() ); 
    }

}
