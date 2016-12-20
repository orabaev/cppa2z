#include <catch.hpp>
#include <sstream>
#include <strstream>

using namespace std;

TEST_CASE( "ends", "[std] [streams] [manipulators]" ) {
    
    SECTION( "insert null character" ) {
        ostrstream sout;

        sout << "0123456" << ends;
        const char* str = sout.str(); 
        
        REQUIRE( '\0' == str[7] );

        sout.freeze(false);
    }
 
}

TEST_CASE( "quoted", "[std] [streams] [manipulators]" ) {
    
    SECTION( "<< quoted" ) {
        ostringstream sout;

        sout << quoted("Hello C++");

        REQUIRE( "\"Hello C++\"" == sout.str() );
    }

    SECTION( "<< quoted custom delimiter" ) {
        ostringstream sout;

        sout << quoted("Hello C++", '|');

        REQUIRE( "|Hello C++|" == sout.str() );
    }

    SECTION( "<< quoted with default escape" ) {
        ostringstream sout;

        sout << quoted("Hello \\ C++");

        REQUIRE( "\"Hello \\\\ C++\"" == sout.str() );
    }

    SECTION( "<< quoted with custom delimiter and escape" ) {
        ostringstream sout;

        sout << quoted("Hello ? C++", '|', '?');

        REQUIRE( "|Hello ?? C++|" == sout.str() );
    }

    SECTION( ">> quoted" ) {
        istringstream sin{"\"Hello C++\""};
        string str;
            
        sin >> quoted(str);

        REQUIRE( "Hello C++" == str );
    }

    SECTION( ">> quoted custom delimiter" ) {
        istringstream sin{"|Hello C++|"};
        string str;
            
        sin >> quoted(str, '|');

        REQUIRE( "Hello C++" == str );
    }

    SECTION( ">> quoted with default escape" ) {
        istringstream sin{"\"Hello \\\\ C++\""};
        string str;

        sin >> quoted(str);

        REQUIRE( "Hello \\ C++" == str );
    }

    SECTION( ">> quoted with custom delimiter and escape" ) {
        istringstream sin{"|Hello ?? C++|"};
        string str;

        sin >> quoted(str, '|', '?');

        REQUIRE( "Hello ? C++" == str );
    }

}
