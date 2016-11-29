#include <catch.hpp>
#include <sstream>
#include <iostream>

using namespace std;

TEST_CASE( ">>", "[std] [iterator] [stream]" ) {
    
    SECTION( "read all values from the stream" ) {
        istringstream sin{"1 2   5  6 \n8 \n\n\n10 "};
        
        int x = 0;
        int counter = 0;
        while (sin >> x) ++counter;

        REQUIRE( 6 == counter );
        REQUIRE( sin.eof() );
        REQUIRE( sin.fail() );
        REQUIRE_FALSE( sin.bad() );
    }

    SECTION( "read two int values from istream" ) {
        istringstream sin{"1 2"};

        int x = 0;

        REQUIRE( sin >> x );
        REQUIRE( 1 == x );

        REQUIRE( sin >> x );
        REQUIRE( 2 == x );

        REQUIRE_FALSE ( sin >> x );
        REQUIRE( sin.eof() );
    } 

    SECTION( "try read two int values from istream, first value is not an int" ) {
        istringstream sin{"a 2"};

        int x = 0;

        REQUIRE_FALSE( sin >> x );
        
        bool recoverable_error = sin.fail();
        REQUIRE( recoverable_error );

        // recover
        sin.clear();
        sin.ignore(1);

        REQUIRE( sin >> x );
        REQUIRE( 2 == x );

        REQUIRE_FALSE( sin >> x );
        REQUIRE( sin.eof() );
    }

}

TEST_CASE( "gcount", "[std] [iterator] [stream]" ) {
    
    SECTION( "number of characters extracted after calling get" ) {
        istringstream sin{"12345"};
        
        constexpr streamsize max_characters_to_extract = 20;
        char buffer[max_characters_to_extract]; 
        
        sin.get(buffer, max_characters_to_extract);

        auto characters_extracted = sin.gcount();

        REQUIRE( 5 == characters_extracted );
    }

    SECTION( "number of characters extracted after calling getline" ) {
        istringstream sin{"12345\n1234567"};
        const streamsize max_characters_to_extract = 20;
        char buffer[max_characters_to_extract]; 
        
        sin.getline(buffer, max_characters_to_extract);

        auto characters_extracted = sin.gcount();
        const streamsize expected_extracted_5_plus_new_line = 6; 

        REQUIRE( expected_extracted_5_plus_new_line == characters_extracted );

        sin.getline(buffer, max_characters_to_extract);

        characters_extracted = sin.gcount();

        REQUIRE( 7 == characters_extracted );
    }

    SECTION( "number of characters extracted after calling ignore with count" ) {
        istringstream sin{"12345"};
       
        const streamsize ignore_count = 3; 
        sin.ignore(ignore_count);

        auto characters_extracted = sin.gcount();

        REQUIRE( ignore_count == characters_extracted );
    }

    SECTION( "number of characters extracted after calling ignore with delimiter" ) {
        istringstream sin{"12345A more text"};

        const char delimiter = 'A'; 
        sin.ignore(20, delimiter);

        auto characters_extracted = sin.gcount();

        const streamsize ignored_including_delimiter = 6; 
        REQUIRE( ignored_including_delimiter == characters_extracted );
    }

    SECTION( "number of characters extracted after calling operator >>" ) {
        istringstream sin{"1 2 3"};
        int x = 0;

        sin >> x;

        REQUIRE( 1 == x );

        auto characters_extracted = sin.gcount();

        REQUIRE( 0 == characters_extracted );
    }

}



























