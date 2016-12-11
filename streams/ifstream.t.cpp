#include <catch.hpp>
#include <sstream>
#include <fstream>

using namespace std;

TEST_CASE( "ifstream.ctor", "[std] [ifstream]" ) {

    ofstream fout("ifstream.tmp");

    SECTION( "default ctor" ) {
        ifstream  fin;

        REQUIRE( fin );
        REQUIRE( -1 == fin.tellg() );
    }

    SECTION( "open existing empty file" ) {
        ifstream  fin("ifstream.tmp");

        REQUIRE( fin );
        REQUIRE( 0 == fin.tellg() );
    }

    SECTION( "ifstream is opened in ios_base::in mode" ) {
        ifstream  fin("ifstream.tmp", ios_base::in);

        REQUIRE( fin );
        REQUIRE( 0 == fin.tellg() );
    }

    SECTION( "ifstream is opened in ios_base::ate mode" ) {
        fout << "ABC" << flush;

        ifstream  fin("ifstream.tmp", ios_base::ate);

        REQUIRE( fin );
        REQUIRE( 3 == fin.tellg() );
    }

    SECTION( "ifstream(const string& filename, ios_base::openmode mode = ios_base::in )" ) {
        string filename{"ifstream.tmp"}; 

        ifstream  fin(filename);

        REQUIRE( fin );
        REQUIRE( 0 == fin.tellg() );
    }

    fout.close();
    REQUIRE( 0 == remove("ifstream.tmp") );
 
}

TEST_CASE( "ifstream.rdbuf", "[std] [ifstream]" ) {

    SECTION( "rdbuf" ) {
        ifstream  sin;

        REQUIRE ( nullptr != sin.rdbuf() );
    }

}
