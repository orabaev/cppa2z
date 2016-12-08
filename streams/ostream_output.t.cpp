#include <catch.hpp>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

TEST_CASE( "operator << ", "[std] [istream] [output]" ) {
    
    SECTION( "output bool" ) {
        ostringstream sout;
        const bool value = true;
        sout << value;
        
        REQUIRE( "1" == sout.str() ); 
    }

    SECTION( "output bool as string" ) {
        ostringstream sout;
        const bool value = true;
        sout << boolalpha << value;
        
        REQUIRE( "true" == sout.str() ); 
    }

    SECTION( "output int" ) {
        ostringstream sout;
        const int value = 1234567;
        sout << value;
        
        REQUIRE( "1234567" == sout.str() ); 
    }

    SECTION( "output double" ) {
        ostringstream sout;
        const double value = 123.4567;
        sout << fixed << value;
        
        REQUIRE( "123.456700" == sout.str() ); 
    }

    SECTION( "output pointer" ) {
        ostringstream sout;
        const int value = 123;
        sout <<  &value;
        
        REQUIRE( "0x" == sout.str().substr(0, 2) ); 
    }

    SECTION( "output nullptr" ) {
        ostringstream sout;
        const void* ptr = nullptr;
        sout <<  ptr;
        
        REQUIRE( "0x0" == sout.str() ); 
    }

}

TEST_CASE( "put", "[std] [istream] [output]" ) {

    SECTION( "insert character" ) {
        ostringstream sout;
        sout.put('A').put('B').put('C');
        
        REQUIRE( "ABC" == sout.str() ); 
    }

    SECTION( "insert null character" ) {
        ostringstream sout;
        sout.put('A').put('\0').put('C');
        
        const auto str = sout.str();
        REQUIRE( 3 == str.size() );

        REQUIRE( 'A'  == str[0] );
        REQUIRE( '\0' == str[1] );
        REQUIRE( 'C'  == str[2] );
    }

}

TEST_CASE( "write", "[std] [istream] [output]" ) {

    SECTION( "insert block of characters" ) {
        ostringstream sout;
        const char buffer[] = {"ABCDE"};
        
        const int size_without_null_char = sizeof(buffer) - 1;
        sout.write(buffer, size_without_null_char);

        REQUIRE( "ABCDE" == sout.str() );  
    }

    SECTION( "insert integer value as block of bytes" ) {
        ostringstream sout;
        const int value = 1234567890; 
        
        sout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        
        auto str = sout.str();
        REQUIRE( sizeof(value) == str.size() );

        const int written_value = *(reinterpret_cast<const int*>(str.data()));
        
        REQUIRE( value == written_value );

    }

}
