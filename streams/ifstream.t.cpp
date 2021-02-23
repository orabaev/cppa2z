#include <catch.hpp>
#include <sstream>
#include <fstream>

using namespace std;

TEST_CASE( "ifstream.ctor", "[std] [ifstream]" ) {

    ofstream fout("ifstream.tmp");

    SECTION( "default ctor" ) {
        ifstream  fin;

        REQUIRE( fin );
        REQUIRE( fin.tellg() == -1 );
    }

    SECTION( "open existing empty file" ) {
        ifstream  fin("ifstream.tmp");

        REQUIRE( fin );
        REQUIRE( fin.tellg() == 0);
    }

    SECTION( "ifstream is opened in ios_base::in mode" ) {
        ifstream  fin("ifstream.tmp", ios_base::in);

        REQUIRE( fin );
        REQUIRE( fin.tellg() == 0 );
    }

    SECTION( "ifstream is opened in ios_base::ate mode" ) {
        fout << "ABC" << flush;

        ifstream  fin("ifstream.tmp", ios_base::ate);

        REQUIRE( fin );
        REQUIRE( fin.tellg() == 3 );
    }

    SECTION( "ifstream(const string& filename, ios_base::openmode mode = ios_base::in)" ) {
        string file_name{"ifstream.tmp"}; 

        ifstream  fin(file_name);

        REQUIRE( fin );
        REQUIRE( fin.tellg() == 0 );
    }

    SECTION( "move ctor" ) {
        fout << "ABC" << flush;

        ifstream  fin1("ifstream.tmp");

        ifstream  fin2(move(fin1));

        REQUIRE( fin2 );
        REQUIRE( fin2.get() == 'A' );
    }

    fout.close();
    REQUIRE( remove("ifstream.tmp") == 0 );
 
}

TEST_CASE( "ifstream.operator=", "[std] [ifstream]" ) {

    ofstream fout("ifstream.tmp");

    SECTION( "operator=" ) {
        ifstream  fin2;
        REQUIRE( fin2.tellg() == -1 ); 

        ifstream  fin1("ifstream.tmp");

        fin2 = move(fin1);

        REQUIRE( fin2.tellg() == 0 );
    }

    fout.close();
    REQUIRE( remove("ifstream.tmp") == 0 );
} 

TEST_CASE( "ifstream.swap", "[std] [ifstream]" ) {

    ofstream fout("ifstream.tmp");

    SECTION( "member swap" ) {
        ifstream  fin1("ifstream.tmp");
        ifstream  fin2;

        REQUIRE( fin1.tellg() == 0 );
        REQUIRE( fin2.tellg() == -1 );

        fin1.swap(fin2);

        REQUIRE( fin1.tellg() == -1 );
        REQUIRE( fin2.tellg() == 0 );
    }

    SECTION( "std::swap" ) {
        ifstream  fin1("ifstream.tmp");
        ifstream  fin2;

        REQUIRE( fin1.tellg() == 0 );
        REQUIRE( fin2.tellg() == -1 );

        std::swap(fin1, fin2);

        REQUIRE( fin1.tellg() == -1 );
        REQUIRE( fin2.tellg() == 0 );
    }

    fout.close();
    REQUIRE( 0 == remove("ifstream.tmp") );

}

TEST_CASE( "ifstream.rdbuf", "[std] [ifstream]" ) {

    SECTION( "rdbuf" ) {
        ifstream  fin;

        REQUIRE ( fin.rdbuf() != nullptr );
    }

}

TEST_CASE( "ifstream.is_open", "[std] [ifstream]" ) {

    SECTION( "is_open when file exists" ) {
        ofstream  fout("ifstream.tmp");

        ifstream  fin("ifstream.tmp");
         
        REQUIRE( fin.is_open() );

        remove("ifstream.tmp");
    }

    SECTION( "is_open when default contructed" ) {
        ifstream  fin;
        
        REQUIRE_FALSE( fin.is_open() );
    }

    SECTION( "is_open when file does not exist" ) {
        ifstream  fin("non_existant_file");
         
        REQUIRE_FALSE( fin.is_open() );
    }

}

TEST_CASE( "ifstream.open", "[std] [ifstream]" ) {

    ofstream  fout("ifstream.tmp");

    SECTION( "open when file exists" ) {
        ifstream  fin;
        fin.open("ifstream.tmp");
         
        REQUIRE( fin );
    }

    SECTION( "open when file does not exist" ) {
        ifstream  fin;
        fin.open("non_existant_file");
         
        REQUIRE_FALSE( fin );
    }

    SECTION( "void open(const std::string &filename, ios_base::openmode mode = ios_base::in )" ) {
        ifstream  fin;

        string file_name{"ifstream.tmp"};
        fin.open(file_name);
         
        REQUIRE( fin );
    }

    remove("ifstream.tmp");

}

TEST_CASE( "ifstream.close", "[std] [ifstream]" ) {

    ofstream  fout("ifstream.tmp");

    SECTION( "close opened file" ) {
        ifstream fin("ifstream.tmp");

        fin.close();

        REQUIRE( fin );
    }

    SECTION( "close non opened file" ) {
        ifstream fin;
        
        REQUIRE( fin );

        fin.close();

        REQUIRE_FALSE( fin );
    }

    remove("ifstream.tmp");

}
