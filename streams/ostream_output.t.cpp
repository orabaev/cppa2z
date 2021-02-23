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
        
        REQUIRE( sout.str() == "1" ); 
    }

    SECTION( "output bool as string" ) {
        ostringstream sout;
        const bool value = true;
        sout << boolalpha << value;
        
        REQUIRE( sout.str() == "true" ); 
    }

    SECTION( "output int" ) {
        ostringstream sout;
        const int value = 1234567;
        sout << value;
        
        REQUIRE( sout.str() == "1234567" ); 
    }

    SECTION( "output double" ) {
        ostringstream sout;
        const double value = 123.4567;
        sout << fixed << value;
        
        REQUIRE( sout.str() == "123.456700" ); 
    }

    SECTION( "output pointer" ) {
        ostringstream sout;
        const int value = 123;
        sout <<  &value;
        
        REQUIRE(  sout.str().substr(0, 2) == "0x" ); 
    }

    SECTION( "output nullptr" ) {
        ostringstream sout;
        const void* ptr = nullptr;
        sout <<  ptr;
        
#ifdef __linux__
        REQUIRE( "0" == sout.str() );
#else
        REQUIRE( "0x0" == sout.str() );
#endif
    }

}

TEST_CASE( "put", "[std] [istream] [output]" ) {

    SECTION( "insert character" ) {
        ostringstream sout;
        sout.put('A').put('B').put('C');
        
        REQUIRE( sout.str() == "ABC" ); 
    }

    SECTION( "insert null character" ) {
        ostringstream sout;
        sout.put('A').put('\0').put('C');
        
        const auto str = sout.str();
        REQUIRE( str.size() == 3 );

        REQUIRE( str[0] == 'A' );
        REQUIRE( str[1] == '\0' );
        REQUIRE( str[2] == 'C' );
    }

}

TEST_CASE( "write", "[std] [istream] [output]" ) {

    SECTION( "insert block of characters" ) {
        ostringstream sout;
        const char buffer[] = {"ABCDE"};
        
        const int size_without_null_char = sizeof(buffer) - 1;
        sout.write(buffer, size_without_null_char);

        REQUIRE( sout.str() == "ABCDE" );  
    }

    SECTION( "insert integer value as block of bytes" ) {
        ostringstream sout;
        const int value = 1234567890; 
        
        sout.write(reinterpret_cast<const char*>(&value), sizeof(value));
        
        auto str = sout.str();
        REQUIRE( str.size() == sizeof(value) );

        const int written_value = *(reinterpret_cast<const int*>(str.data()));
        
        REQUIRE( written_value == value );
    }

}
