#include <catch.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

TEST_CASE( "tellg", "[std] [istream] [misc]" ) {
    
    SECTION( "input position indicator when nothing was read of the istream" ) {
        istringstream sin{"0123"};
        
        REQUIRE( 0 == sin.tellg() );
    }

    SECTION( "input position indicator after read input" ) {
        istringstream sin{"Hello C++   ABC"};
        string str; 

        sin >> str;
        REQUIRE( 5 == sin.tellg() );

        sin >> str;
        REQUIRE( 9 == sin.tellg() );
    }

    SECTION( "input position indicator after read input" ) {
        istringstream sin{"word"};
        string str; 

        sin >> str;
        REQUIRE( -1 == sin.tellg() );
    }

}

TEST_CASE( "seekg", "[std] [istream] [misc]" ) {
    
    SECTION( "set input position indicator to second character" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE( sin.seekg(1) );

        REQUIRE( 1 == sin.tellg() );
        REQUIRE( 'B' == sin.get() );
    }

    SECTION( "set input position indicator one character beyond" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE( sin.seekg(4) );

        REQUIRE( 4 == sin.tellg() );
        REQUIRE( EOF == sin.get() );
        REQUIRE( -1 == sin.tellg() );
    }

    SECTION( "try to set input position indicator more than one character beyond" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE_FALSE( sin.seekg(5) );

        REQUIRE( -1 == sin.tellg() );
    }

    SECTION( "set input position indicator using offset from the beginning" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(1, ios_base::beg) );
        REQUIRE( 1 == sin.tellg() );

        REQUIRE_FALSE( sin.seekg(-7, ios_base::beg) );
        REQUIRE( -1 == sin.tellg() );
    }

    SECTION( "set input position indicator using offset from the end" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(-1, ios_base::end) );
        REQUIRE( 3 == sin.tellg() );

        REQUIRE_FALSE( sin.seekg(7, ios_base::end) );
        REQUIRE( -1 == sin.tellg() );
    }

    SECTION( "set input position indicator using offset from the current position" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(2, ios_base::cur) );
        REQUIRE( 2 == sin.tellg() );

        REQUIRE( sin.seekg(-1, ios_base::cur) );
        REQUIRE( 1 == sin.tellg() );

        REQUIRE( sin.seekg(3, ios_base::cur) );
        REQUIRE( 4 == sin.tellg() );

        REQUIRE_FALSE( sin.seekg(1, ios_base::cur) );
    }
}

namespace {
struct Person {
    string Name;
    int    Age;
};

istream& operator>>(istream& sin, Person& person) {
    // sentry -----
    istream::sentry entry(sin);
    // ------ sentry
    if (entry) {
        sin >> person.Name >> person.Age;    
    }

    return sin;
} 

TEST_CASE( "sentry", "[std] [istream] [misc]" ) {
    
    SECTION( "use sentry when implementing operator>> for input stream" ) {
        istringstream sin{"Bill 70"};
        
        Person person{"NA", 0}; 
        REQUIRE( sin >> person );
        
        REQUIRE( "Bill" == person.Name );
        REQUIRE(     70 == person.Age  );
    }

} 
} // namespace

TEST_CASE( "sync", "[std] [istream] [misc]" ) {
    
    SECTION( "sync file stream while underlying file has changed" ) {
        ofstream fout("sync.tmp");
        REQUIRE( fout );
        fout << "abc"; 
        fout.close();

        ifstream fin("sync.tmp"); 
        REQUIRE( fin );

        REQUIRE( 'a' == fin.get() );

        fout.open("sync.tmp");
        fout << "ABC"; 
        fout.close();

        // sync ------
        REQUIRE ( 0 == fin.sync() );
        // ------ sync

        REQUIRE( 'B' == fin.get() );
        REQUIRE( 'C' == fin.get() );
    }

}
