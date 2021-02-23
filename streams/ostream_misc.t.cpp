#include <catch.hpp>
#include <sstream>
#include <fstream>

using namespace std;

TEST_CASE( "tellp", "[std] [ostream] [misc]" ) {
    
    SECTION( "ouput position indicator when nothing was inserted into the stream" ) {
        ostringstream sout;
        
        REQUIRE( sout.tellp() == 0 );
    }

    SECTION( "ouput position indicator when characters were inserted into the stream" ) {
        ostringstream sout;

        sout  << 'A';
        REQUIRE( sout.tellp() == 1 );

        sout  << "BCD";
        REQUIRE( sout.tellp() == 4 );
    }

}

TEST_CASE( "seekp", "[std] [ostream] [misc]" ) {
    
    SECTION( "set ouput position indicator to second character" ) {
        ostringstream sout;

        sout << "ABCD";
        REQUIRE( sout.str() == "ABCD" ); 

        REQUIRE( sout.seekp(2) );

        sout << "FG";
        REQUIRE( sout.str() == "ABFG" ); 
    }

    SECTION( "try to set ouput position one character beyond" ) {
        ostringstream sout;

        sout << "ABCD";

        REQUIRE_FALSE( sout.seekp(5) );
    }

    SECTION( "set output position indicator using offset from the beginning" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(1, ios_base::beg) );
        REQUIRE( sout.tellp() == 1 );

        REQUIRE_FALSE( sout.seekp(-7, ios_base::beg) );
        REQUIRE( sout.tellp() == -1 );
    }

    SECTION( "set output  position indicator using offset from the end" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(-1, ios_base::end) );
        REQUIRE( sout.tellp() == 3 );

        REQUIRE_FALSE( sout.seekp(7, ios_base::end) );
        REQUIRE( sout.tellp() == -1 );
    }

    SECTION( "set input position indicator using offset from the current position" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(2, ios_base::cur) );
        REQUIRE( sout.tellp() == 2 );

        REQUIRE( sout.seekp(-1, ios_base::cur) );
        REQUIRE( sout.tellp() == 1 );

        REQUIRE( sout.seekp(3, ios_base::cur) );
        REQUIRE( sout.tellp() == 4 );

        REQUIRE_FALSE( sout.seekp(1, ios_base::cur) );
    }
}

namespace {
struct Person {
    string Name;
    int    Age;
};

ostream& operator << (ostream& sout, Person& person) {
    // sentry -----
    ostream::sentry entry(sout);
    // ------ sentry
    if (entry) {
        sout << person.Name << ' ' <<  person.Age;    
    }

    return sout;
} 

TEST_CASE( " sentry", "[std] [ostream] [misc]" ) {
    
    SECTION( "use sentry when implementing operator<< for output stream" ) {
        ostringstream sout;
         
        Person person{"Bill", 70}; 

        REQUIRE( sout << person );

        REQUIRE( sout.str() == "Bill 70" );
    }

} 
} // namespace

TEST_CASE( "flush", "[std] [ostream] [misc]" ) {
    
    SECTION( "flush file stream to sync with underlying file" ) {
        ofstream fout("flush.tmp");
        REQUIRE( fout );
        fout << "abc"; 

        string str;
        ifstream fin("flush.tmp"); 
        REQUIRE_FALSE( fin >> str );
        fin.close();

        // flush ----
        REQUIRE( fout.flush() );
        // ---- flush

        fin.open("flush.tmp");
        REQUIRE( fin >> str );

        REQUIRE( str == "abc" );
    }

    remove("flush.tmp");
}
