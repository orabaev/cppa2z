#include <catch.hpp>
#include <sstream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <iostream>

using namespace std;

TEST_CASE( "showpoint", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< showpoint << floating-point with zeroes after decimal point" ) {
        ostringstream sout;

        sout << showpoint << 27.0 ;

        REQUIRE( sout.str() == "27.0000" );
    }

    SECTION( "<< showpoint << floating-point with no zeroes after decimal point" ) {
        ostringstream sout;

        sout << showpoint << 27.12 ;

        REQUIRE( sout.str() == "27.1200" );
    }

}

TEST_CASE( "noshowpoint", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< noshowpoint << floating-point with zeroes after decimal point" ) {
        ostringstream sout;

        sout << noshowpoint << 27.0 ;

        REQUIRE( sout.str() == "27" );
    }

    SECTION( "<< noshowpoint << floating-point with non zeroes after decimal point" ) {
        ostringstream sout;

        sout << noshowpoint << 27.12 ;

        REQUIRE( sout.str() == "27.12" );
    }

}

TEST_CASE( "fixed", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to fixed " ) {
        ostringstream sout;
        
        sout << fixed << 0.1 << ' ' << 2.0011 << ' ' << 2.123456789;
        
        REQUIRE( sout.str() == "0.100000 2.001100 2.123457" ); 
    }

}

TEST_CASE( "scientific", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to scientific " ) {
        ostringstream sout;
        
        sout << scientific << 0.1 << ' ' << 0.0011 << ' ' << 1234.0001;

        REQUIRE( sout.str() == "1.000000e-01 1.100000e-03 1.234000e+03" ); 
    }

}

TEST_CASE( "hexfloat", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to hexfloat " ) {
        ostringstream sout;
        
        sout << hexfloat << 0.1 << ' ' << 0.0011 << ' ' << 1234.0001;

        REQUIRE( sout.str() == "0x1.999999999999ap-4 0x1.205bc01a36e2fp-10 0x1.348001a36e2ebp+10" ); 
    }

}

TEST_CASE( "defaultfloat", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default formating for floating-point to defaultfloat" ) {
        ostringstream sout;
        
        sout << defaultfloat << 0.1 << ' ' << 2.0011 << ' ' << 2.123456789;
        
        REQUIRE( sout.str() == "0.1 2.0011 2.12346" ); 
    }

}

TEST_CASE( "setprecision", "[std] [streams] [manipulators]" ) {
   
    SECTION( "set default fill character for adjusted text" ) {
        ostringstream sout;
        const long double pi = 3.14159265358979;;
        
        sout << pi
             << ' '
             << setprecision(10) << pi
             << ' '
             << setprecision(15) << pi;

        REQUIRE( sout.str() == "3.14159 3.141592654 3.14159265358979" );
    }

}
