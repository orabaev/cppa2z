#include <catch.hpp>
#include <sstream>

using namespace std;

TEST_CASE( "left", "[std] [streams] [manipulators]" ) {
    
    SECTION( "left adjust text" ) {
        ostringstream sout;

        sout << setw(10) << left << "ABCDE";
        
        REQUIRE( sout.str() == "ABCDE     " ); 
    }

    SECTION( "left adjust number" ) {
        ostringstream sout;

        sout << setw(10) << left << 12345;
        
        REQUIRE( sout.str() == "12345     " ); 
    }

    SECTION( "left adjust text with custom fill character" ) {
        ostringstream sout;

        sout << setw(10) << left << setfill('@')  << "ABCDE";
        
        REQUIRE( sout.str() == "ABCDE@@@@@" ); 
    }

}

TEST_CASE( "right", "[std] [streams] [manipulators]" ) {
    
    SECTION( "right adjust text" ) {
        ostringstream sout;

        sout << setw(10) << right << "ABCDE";
        
        REQUIRE( sout.str() == "     ABCDE" ); 
    }

    SECTION( "right adjust number" ) {
        ostringstream sout;

        sout << setw(10) << right << 12345;
        
        REQUIRE( sout.str() == "     12345" ); 
    }

    SECTION( "left adjust text with custom fill character" ) {
        ostringstream sout;

        sout << setw(10) << right << setfill('@')  << "ABCDE";
        
        REQUIRE( sout.str() == "@@@@@ABCDE" ); 
    }

}

TEST_CASE( "internal", "[std] [streams] [manipulators]" ) {
    
    SECTION( "insert fill character at internal point for negative integer" ) {
        ostringstream sout;

        sout << setw(10) << internal << -1;
        
        REQUIRE( sout.str() == "-        1" ); 
    }

    SECTION( "insert fill character at internal point for hex output" ) {
        ostringstream sout;

        sout << setw(10) << internal << hex << showbase << 255;
        
        REQUIRE( sout.str() == "0x      ff" ); 
    }

    SECTION( "insert fill character at internal point for money output" ) {
        ostringstream sout;
        sout.imbue(locale("en_US"));

        int cents = 199;
        sout << setw(10) << internal << showbase << put_money(cents);

#ifdef __linux__
        REQUIRE( sout.str() == "$1.99     " );
#else
        REQUIRE( sout.str() == "$     1.99" );
#endif
    }

}

TEST_CASE( "setfill", "[std] [streams] [manipulators]" ) {
    
    SECTION( "set default fill character for adjusted text" ) {
        ostringstream sout;

        sout << setw(25) << left << setfill('*') <<  "ABCDE";
        REQUIRE( sout.str() == "ABCDE********************" ); 

        sout.str(string{});
        sout << setw(25) << left << setfill(' ') <<  "ABCDE";
        REQUIRE( sout.str() == "ABCDE                    " ); 
    }

}

TEST_CASE( "setw", "[std] [streams] [manipulators]" ) {
   
    SECTION( "set width for adjusted text" ) {
        ostringstream sout;
        
        sout << setw(1) << "ABC";
        REQUIRE( sout.str() == "ABC" );

        sout.str(string{});
        sout << setw(10) << "ABC";
        REQUIRE( sout.str() == "       ABC" );
    }

}
