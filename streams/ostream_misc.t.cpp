#include <catch.hpp>
#include <sstream>
#include <fstream>

using namespace std;

TEST_CASE( "tellp", "[std] [ostream] [misc]" ) {
    
    SECTION( "ouput position indicator when nothing was inserted into the stream" ) {
        ostringstream sout;
        
        REQUIRE( 0 == sout.tellp() );
    }

    SECTION( "ouput position indicator when characters were inserted into the stream" ) {
        ostringstream sout;

        sout  << 'A';
        REQUIRE( 1 == sout.tellp() );

        sout  << "BCD";
        REQUIRE( 4 == sout.tellp() );
    }

}

TEST_CASE( "seekp", "[std] [ostream] [misc]" ) {
    
    SECTION( "set ouput position indicator to second character" ) {
        ostringstream sout;

        sout << "ABCD";
        REQUIRE( "ABCD" == sout.str() ); 

        REQUIRE( sout.seekp(2) );

        sout << "FG";
        REQUIRE( "ABFG" == sout.str() ); 
    }

    SECTION( "try to set ouput position one character beyond" ) {
        ostringstream sout;

        sout << "ABCD";

        REQUIRE_FALSE( sout.seekp(5) );
    }

    SECTION( "set output position indicator using offset from the beginning" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(1, ios_base::beg) );
        REQUIRE( 1 == sout.tellp() );

        REQUIRE_FALSE( sout.seekp(-7, ios_base::beg) );
        REQUIRE( -1 == sout.tellp() );
    }

    SECTION( "set output  position indicator using offset from the end" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(-1, ios_base::end) );
        REQUIRE( 3 == sout.tellp() );

        REQUIRE_FALSE( sout.seekp(7, ios_base::end) );
        REQUIRE( -1 == sout.tellp() );
    }

    SECTION( "set input position indicator using offset from the current position" ) {
        ostringstream sout{"0123"};
        
        REQUIRE( sout.seekp(2, ios_base::cur) );
        REQUIRE( 2 == sout.tellp() );

        REQUIRE( sout.seekp(-1, ios_base::cur) );
        REQUIRE( 1 == sout.tellp() );

        REQUIRE( sout.seekp(3, ios_base::cur) );
        REQUIRE( 4 == sout.tellp() );

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

        REQUIRE( "Bill 70"  ==  sout.str() );
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

        REQUIRE( "abc" == str );
    }

    REQUIRE( 0 == remove("flush.tmp") );
}
