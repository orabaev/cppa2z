#include <catch.hpp>
#include <fstream>
#include <stdio.h>

using namespace std;

TEST_CASE( "ofstream.ctor", "[std] [streams] [ofstream]" ) {

    SECTION( "[out] same as  [out | trunc] create new or truncate existing file, can write anywhere" ) {
        ofstream fout("ofstream.tmp", ios_base::out);

        bool file_was_created = fout.is_open();
        REQUIRE( file_was_created );

        fout << "ABC";
        bool appended_three_characters = fout.tellp() == 3;
        REQUIRE( appended_three_characters );

        fout << "DEF";
        appended_three_characters = fout.tellp() == 6;
        REQUIRE( appended_three_characters );

        REQUIRE( fout.seekp(0) );
        fout << "123";
        bool overwrote_at_the_beginning = fout.tellp() == 3;
        REQUIRE( overwrote_at_the_beginning );
       
        ofstream fout_truncate_existing("ofstream.tmp", ios_base::out);
        fout_truncate_existing.close();
        
        ifstream fin("ofstream.tmp");
        bool file_is_empty = fin.get() == -1;
        
        REQUIRE( file_is_empty ); 
    }

    SECTION( "[out | app] create new or use existing, always write at the end" ) {
        ofstream fout_create_new("ofstream.tmp", ios_base::out | ios_base::app);
        REQUIRE( 0 == fout_create_new.tellp() );
        fout_create_new << "ABC";
        REQUIRE( 3 == fout_create_new.tellp() );
        fout_create_new.close();

        ofstream fout("ofstream.tmp", ios_base::out | ios_base::app);

        bool wrote_at_the_end = fout.tellp() == 3;
        REQUIRE( wrote_at_the_end );

        fout.seekp(0);
        fout << "DEF";

        wrote_at_the_end = fout.tellp() == 6;
        REQUIRE( wrote_at_the_end );
    }

    SECTION( "[out | in | ate] always use existing file, seeks at the end of the stream but can write anywhere" ) {
        ofstream fout_try_to_open("ofstream.tmp", ios_base::out | ios_base::in | ios_base::ate);
        bool file_does_not_exist = fout_try_to_open.tellp() == -1;
        REQUIRE( file_does_not_exist );

        ofstream fout_create_new("ofstream.tmp", ios_base::out);
        REQUIRE( 0 == fout_create_new.tellp() );
        fout_create_new << "ABC";
        REQUIRE( 3 == fout_create_new.tellp() );
        fout_create_new.close();

        ofstream fout_make_sure_file_exists("ofstream.tmp", ios_base::out);
        fout_make_sure_file_exists << "ABC";
        fout_make_sure_file_exists.close(); 

        ofstream fout("ofstream.tmp", ios_base::out | ios_base::in | ios_base::ate);

        bool will_write_at_the_end = fout.tellp() == 3;
        REQUIRE( will_write_at_the_end );

        fout << "DEF";

        bool wrote_at_the_end = fout.tellp() == 6;
        REQUIRE( wrote_at_the_end );

        fout.seekp(0);
        fout << "123"; 
        bool wrote_at_the_beginning = fout.tellp() == 3; 
        REQUIRE( wrote_at_the_beginning  );
    }

    SECTION( "default ctor" ) {
        ofstream fout;

        REQUIRE( -1 == fout.tellp() );
    }

    SECTION( "ctor filename as string" ) {
        const string file_name = "ofstream.tmp";
        ofstream fout(file_name, ios_base::out);

        REQUIRE( fout );
    }

    SECTION( "move ctor" ) {
        ofstream fout1("ofstream.tmp");
        ofstream fout2(move(fout1));

        REQUIRE( 0 == fout2.tellp() );
    }

    remove("ofstream.tmp");

}

TEST_CASE( "ofstream.operator=", "[std] [streams] [ofstream]" ) {

    SECTION( "operator=" ) {
        ofstream  fout2;
        REQUIRE( -1 == fout2.tellp() ); 

        ofstream  fout1("ofstream.tmp");

        fout2 = move(fout1);

        REQUIRE( 0 == fout2.tellp() );
    }

    REQUIRE( 0 == remove("ofstream.tmp") );
} 

TEST_CASE( "ofstream.swap", "[std] [streams] [ofstream]" ) {

    SECTION( "member swap" ) {
        ofstream  fout1("ofstream.tmp");
        ofstream  fout2;

        REQUIRE(  0 == fout1.tellp() );
        REQUIRE( -1 == fout2.tellp() );

        fout1.swap(fout2);

        REQUIRE( -1 == fout1.tellp() );
        REQUIRE(  0 == fout2.tellp() );
    }

    SECTION( "std::swap" ) {
        ofstream  fout1("ofstream.tmp");
        ofstream  fout2;

        REQUIRE(  0 == fout1.tellp() );
        REQUIRE( -1 == fout2.tellp() );

        std::swap(fout1, fout2);

        REQUIRE( -1 == fout1.tellp() );
        REQUIRE(  0 == fout2.tellp() );
    }

    REQUIRE( 0 == remove("ofstream.tmp") );
}

TEST_CASE( "ofstream.rdbuf", "[std] [streams] [ofstream]" ) {

    SECTION( "rdbuf" ) {
        ofstream  fout;

        REQUIRE ( nullptr != fout.rdbuf() );
    }

}

TEST_CASE( "ofstream.is_open", "[std] [streams] [ofstream]" ) {

    SECTION( "is_open file exist or created new" ) {
        ofstream  fout("ofstream.tmp");

        REQUIRE( fout.is_open() );
    }

    SECTION( "is_open when default contructed" ) {
        ofstream  fout;
        
        REQUIRE_FALSE( fout.is_open() );
    }

    SECTION( "is_open file must exist" ) {
        ofstream  fout("ofstream.tmp", ios_base::out | ios_base::in | ios_base::ate);
         
        REQUIRE_FALSE( fout.is_open() );
    }

    remove("ofstream.tmp");
}

TEST_CASE( "ofstream.open", "[std] [streams] [ofstream]" ) {

    SECTION( "open when file exists" ) {
        ofstream("ofstream.tmp");
        
        ofstream  fout;
        fout.open("ofstream.tmp");
         
        REQUIRE( fout );
    }

    SECTION( "open when file does not exist but will be created on open" ) {
        ofstream  fout;
        fout.open("ofstream.tmp");
         
        REQUIRE( fout );
    }

    SECTION( "open when file does not exist" ) {
        ofstream  fout;
        fout.open("ofstream.tmp", ios_base::out | ios_base::in | ios_base::ate);
         
        REQUIRE_FALSE( fout );
    }

    remove("ofstream.tmp");

}

TEST_CASE( "ofstream.close", "[std] [streams]  [ofstream]" ) {

    SECTION( "close opened file" ) {
        ofstream fout("ofstream.tmp");

        fout.close();

        REQUIRE( fout );
    }

    SECTION( "close non opened file" ) {
        ofstream fout;
        
        REQUIRE( fout );

        fout.close();

        REQUIRE_FALSE( fout );
    }

    remove("ofstream.tmp");

}
