#include <catch.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

TEST_CASE( "tellg", "[std] [istream] [misc]" ) {
    
    SECTION( "input position indicator when nothing was read of the istream" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.tellg() == 0 );
    }

    SECTION( "input position indicator when istream is empty" ) {
        istringstream sin;
        
        REQUIRE( sin.tellg() == 0 );
    }

    SECTION( "input position indicator after read input" ) {
        istringstream sin{"Hello C++   ABC"};
        string str; 

        sin >> str;
        REQUIRE( sin.tellg() == 5 );

        sin >> str;
        REQUIRE( sin.tellg() == 9 );
    }

    SECTION( "input position indicator after read input" ) {
        istringstream sin{"word"};
        string str; 

        sin >> str;
        REQUIRE( sin.tellg() == -1 );
    }

}

TEST_CASE( "seekg", "[std] [istream] [misc]" ) {
    
    SECTION( "set input position indicator to second character" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE( sin.seekg(1) );

        REQUIRE( sin.tellg() == 1 );
        REQUIRE( sin.get() == 'B' );
    }

    SECTION( "set input position indicator one character beyond" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE( sin.seekg(4) );

        REQUIRE( sin.tellg() == 4 );
        REQUIRE( sin.get() == EOF );
        REQUIRE( sin.tellg() == -1 );
    }

    SECTION( "try to set input position indicator more than one character beyond" ) {
        istringstream sin{"ABCD"};
        
        REQUIRE_FALSE( sin.seekg(5) );

        REQUIRE( sin.tellg() == -1 );
    }

    SECTION( "set input position indicator using offset from the beginning" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(1, ios_base::beg) );
        REQUIRE( sin.tellg() == 1 );

        REQUIRE_FALSE( sin.seekg(-7, ios_base::beg) );
        REQUIRE( sin.tellg() == -1 );
    }

    SECTION( "set input position indicator using offset from the end" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(-1, ios_base::end) );
        REQUIRE( sin.tellg() == 3 );

        REQUIRE_FALSE( sin.seekg(7, ios_base::end) );
        REQUIRE( sin.tellg() == -1 );
    }

    SECTION( "set input position indicator using offset from the current position" ) {
        istringstream sin{"0123"};
        
        REQUIRE( sin.seekg(2, ios_base::cur) );
        REQUIRE( sin.tellg() == 2 );

        REQUIRE( sin.seekg(-1, ios_base::cur) );
        REQUIRE( sin.tellg() == 1 );

        REQUIRE( sin.seekg(3, ios_base::cur) );
        REQUIRE( sin.tellg() == 4 );

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
        
        REQUIRE(  person.Name == "Bill" );
        REQUIRE(  person.Age == 70 );
    }

} 
} // namespace

// sync does not work on linux
#ifndef __linux__
TEST_CASE( "sync", "[std] [istream] [misc]" ) {
    
    SECTION( "sync file stream while underlying file has changed" ) {
        ofstream fout("sync.tmp");
        REQUIRE( fout );
        fout << "abc"; 
        fout.close();

        ifstream fin("sync.tmp"); 
        REQUIRE( fin );

        REQUIRE( fin.get() == 'a' );

        fout.open("sync.tmp");
        fout << "ABC"; 
        fout.close();

        // sync ------
        REQUIRE ( fin.sync() == 0 );
        // ------ sync

        REQUIRE( fin.get() == 'B' );
        REQUIRE( fin.get() == 'C' );
    }

    REQUIRE( remove("sync.tmp") == 0 );

}
#endif
