#include <catch.hpp>
#include <sstream>
#include <fstream>

using namespace std;

TEST_CASE( "unitbuf", "[std] [streams] [manipulators]" ) {
    
    SECTION( "automatically flushes the buffer after each output operation" ) {
        ofstream fout("unitbuf.tmp");;
        fout << unitbuf << "flushed";
        
        ifstream fin("unitbuf.tmp");;
        string str;
        fin >> str; 

        REQUIRE( str == "flushed" );
        
        fout.close();
        fin.close();
        remove("unitbuf.tmp");
    }

}

TEST_CASE( "nounitbuf", "[std] [streams] [manipulators]" ) {
    
    SECTION( "does not automatically flush the buffer after each output operation" ) {
        ofstream fout("unitbuf.tmp");;
        fout << unitbuf;
        fout << nounitbuf << "not flushed";
        
        ifstream fin("unitbuf.tmp");;
        string str;
        REQUIRE_FALSE( fin >> str );
        
        fout.close();
        fin.close();
        remove("unitbuf.tmp");
    }

}

TEST_CASE( "manipulator.flush", "[std] [streams] [manipulators]" ) {
    
    SECTION( "flush file stream to sync with underlying file" ) {
        ofstream fout("flush.tmp");
        REQUIRE( fout );
        fout << "abc"; 

        string str;
        ifstream fin("flush.tmp"); 
        REQUIRE_FALSE( fin >> str );
        fin.close();

        // flush ----
        REQUIRE( fout << flush );
        // ---- flush

        fin.open("flush.tmp");
        REQUIRE( fin >> str );

        REQUIRE( str == "abc" );
    }

    remove("flush.tmp");
}

TEST_CASE( "endl", "[std] [ostream] [misc]" ) {
    
    SECTION( "insert new line character flush file stream to sync with underlying file" ) {
        ofstream fout("endl.tmp");
        REQUIRE( fout );
        fout << "abc" << '\n'; 

        string str;
        ifstream fin("endl.tmp"); 
        REQUIRE_FALSE( fin >> str );
        fin.close();

        // endl ----
        fout << "def" << endl; 
        // ---- endl

        fin.open("endl.tmp");

        getline(fin, str);
        REQUIRE( str == "abc" );

        getline(fin, str);
        REQUIRE( str == "def" );
    }

    remove("endl.tmp");
}
