#include <catch.hpp>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

TEST_CASE( "operator >>", "[std] [istream] [input]" ) {
    
    SECTION( "read all values from the stream" ) {
        istringstream sin{"1 2   5  6 \n8 \n\n\n10 "};
        
        int x = 0;
        int counter = 0;
        while (sin >> x) ++counter;

        REQUIRE( counter == 6 );
        REQUIRE( sin.eof() );
        REQUIRE( sin.fail() );
        REQUIRE_FALSE( sin.bad() );
    }

    SECTION( "read two int values from istream" ) {
        istringstream sin{"1 2"};

        int x = 0;

        REQUIRE( sin >> x );
        REQUIRE( x == 1 );

        REQUIRE( sin >> x );
        REQUIRE( x == 2 );

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
        REQUIRE( x == 2 );

        REQUIRE_FALSE( sin >> x );
        REQUIRE( sin.eof() );
    }

}

TEST_CASE( "gcount", "[std] [istream] [input]" ) {
    
    SECTION( "number of characters extracted after calling get" ) {
        istringstream sin{"12345"};
        
        constexpr streamsize max_characters_to_extract = 20;
        char buffer[max_characters_to_extract]; 
        
        sin.get(buffer, max_characters_to_extract);

        auto characters_extracted = sin.gcount();

        REQUIRE( characters_extracted == 5 );
    }

    SECTION( "number of characters extracted after calling getline" ) {
        istringstream sin{"12345\n1234567"};
        const streamsize max_characters_to_extract = 20;
        char buffer[max_characters_to_extract]; 
        
        sin.getline(buffer, max_characters_to_extract);

        auto characters_extracted = sin.gcount();
        const streamsize expected_extracted_5_plus_new_line = 6; 

        REQUIRE( characters_extracted == expected_extracted_5_plus_new_line );

        sin.getline(buffer, max_characters_to_extract);

        characters_extracted = sin.gcount();

        REQUIRE( characters_extracted  == 7 );
    }

    SECTION( "number of characters extracted after calling ignore with count" ) {
        istringstream sin{"12345"};
       
        const streamsize ignore_count = 3; 
        sin.ignore(ignore_count);

        auto characters_extracted = sin.gcount();

        REQUIRE( characters_extracted == ignore_count );
    }

    SECTION( "number of characters extracted after calling ignore with delimiter" ) {
        istringstream sin{"12345A more text"};

        const char delimiter = 'A'; 
        sin.ignore(20, delimiter);

        auto characters_extracted = sin.gcount();

        const streamsize ignored_including_delimiter = 6; 
        REQUIRE( characters_extracted == ignored_including_delimiter );
    }

    SECTION( "number of characters extracted after calling operator >>" ) {
        istringstream sin{"1 2 3"};
        int x = 0;

        sin >> x;

        REQUIRE( x == 1 );

        auto characters_extracted = sin.gcount();

        REQUIRE( characters_extracted == 0 );
    }

}

TEST_CASE( "get", "[std] [istream] [input]" ) {
    
    SECTION( "get() single character" ) {
        istringstream sin{"ABC"};
        
        auto ch = sin.get();

        REQUIRE( ch == 'A' );
    }

    SECTION( "get() new line single character" ) {
        istringstream sin{"\nABC"};
        
        auto ch = sin.get();

        REQUIRE( ch == '\n' );
    }

    SECTION( "get() eof" ) {
        istringstream sin;
        
        auto ch = sin.get();

        REQUIRE( ch == EOF );
    }

    SECTION( "get(char_type& ch) single character" ) {
        istringstream sin{"ABC"};
        char ch = 0;

        REQUIRE( sin.get(ch) );

        REQUIRE( ch == 'A' );
    }

    SECTION( "get(char_type* buffer, streamsize count)  3 characters" ) {
        istringstream sin{"123456"};

        const streamsize count_including_null = 4;
        char buffer[count_including_null];

        // getline would return false
        REQUIRE( sin.get(buffer, count_including_null) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        REQUIRE( sin.gcount() == 3 );
    }

    SECTION( "get(char_type* buffer, streamsize count)  eof" ) {
        istringstream sin;

        const streamsize count_including_null = 4;
        char buffer[count_including_null];
        buffer[0] = 'Z';

        REQUIRE_FALSE( sin.get(buffer, count_including_null) );
        // TODO check why behaviour is inconsistent for get(char_type&) returning eof
        REQUIRE( buffer[0] == 0 );
    }

    SECTION( "get(char_type* buffer, streamsize count)  up to new line" ) {
        istringstream sin{"123\n456"};

        const streamsize count_including_null = 20;
        char buffer[count_including_null];

        REQUIRE( sin.get(buffer, count_including_null) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        // after calling getline gcount would return 4
        REQUIRE( sin.gcount() == 3 );
    }

    SECTION( "get(char_type* buffer, streamsize count, char_type delim)  up to new line" ) {
        istringstream sin{"123\n456"};

        const streamsize count_including_null = 20;
        char buffer[count_including_null];
        
        char delim = '\n';
        REQUIRE( sin.get(buffer, count_including_null, delim) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        // after calling getline gcount would return 4
        REQUIRE( sin.gcount() == 3 );
    }

    SECTION( "get(basic_streambuf& streambuf)" ) {
        istringstream     sin{"1234567\n456"};
        ostringstream    sout;
        const string expected{"1234567"};

        sin.get(*sout.rdbuf());

        REQUIRE( expected == sout.str() );
    }

    SECTION( "get(basic_streambuf& streambuf, char_type delim)" ) {
        istringstream     sin{"1234567 A 456"};
        ostringstream    sout;
        const string expected{"1234567 "};

        const char delim = 'A';
        sin.get(*sout.rdbuf(), delim);

        REQUIRE( sout.str() == expected  );
    }

}

TEST_CASE( "getline", "[std] [istream] [input]" ) {

     SECTION( "getline(char_type* buffer, streamsize count)  3 characters" ) {
        istringstream sin{"123456"};

        const streamsize count_including_null = 4;
        char buffer[count_including_null];

        // get would return true
        REQUIRE_FALSE( sin.getline(buffer, count_including_null) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        REQUIRE( sin.gcount() == 3 );
    }

    SECTION( "getline(char_type* buffer, streamsize count)  eof" ) {
        istringstream sin;

        const streamsize count_including_null = 4;
        char buffer[count_including_null];
        buffer[0] = 'Z';

        REQUIRE_FALSE( sin.getline(buffer, count_including_null) );
        REQUIRE( buffer[0] == 0 );
    }

    SECTION( "get(char_type* buffer, streamsize count)  up to new line" ) {
        istringstream sin{"123\n456"};

        const streamsize count_including_null = 20;
        char buffer[count_including_null];

        REQUIRE( sin.getline(buffer, count_including_null) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        // after calling get gcount would return 3
        REQUIRE( sin.gcount() == 4 );
    }

    SECTION( "get(char_type* buffer, streamsize count, char_type delim)  up to new line" ) {
        istringstream sin{"123\n456"};

        const streamsize count_including_null = 20;
        char buffer[count_including_null];
        
        char delim = '\n';
        REQUIRE( sin.getline(buffer, count_including_null, delim) );

        const string expected = "123"; 
        REQUIRE( buffer == expected );
        // after calling get gcount would return 3
        REQUIRE( sin.gcount() == 4 );
    }
   
}

TEST_CASE( "std::getline", "[std] [istream] [input]" ) {

     SECTION( "retrieve full string" ) {
        istringstream      sin{"123456"};
        const string  expected{"123456"}; 
              string       str;

        REQUIRE( getline(sin, str) );

        REQUIRE( str == expected );
    }

    SECTION( "eof" ) {
        istringstream sin;
        string        str;

        REQUIRE_FALSE( getline(sin, str) );
    }

    SECTION( "up to new line" ) {
        istringstream sin{"123\n456"};
        string        str;

        REQUIRE( getline(sin, str) );
        REQUIRE( str == "123" );

        REQUIRE( getline(sin, str) );
        REQUIRE( str == "456" );

        const string before_fail = str;
        REQUIRE_FALSE( getline(sin, str) );
        REQUIRE( str == before_fail );

    }

    SECTION( "up to delimiter" ) {
        istringstream sin{"ABC|DEF"};
        string        str;

        const char delim = '|';
        
        REQUIRE( getline(sin, str, delim) );
        REQUIRE( str == "ABC" );

        REQUIRE( getline(sin, str, delim) );
        REQUIRE( str == "DEF" );

        const string before_fail = str;
        REQUIRE_FALSE( getline(sin, str, delim) );
        REQUIRE( str == before_fail );
    }
   
}

TEST_CASE( "ignore", "[std] [istream] [input]" ) {

     SECTION( "ignore one character" ) {
        istringstream sin{"123456"};

        REQUIRE( sin.ignore(1) ); 

        REQUIRE( sin.get() == '2' );
    }

    SECTION( "ignore three character" ) {
        istringstream  sin{"123456"};

        REQUIRE( sin.ignore(3) ); 

        REQUIRE( sin.get() == '4' );
    }

    SECTION( "ignore three character" ) {
        istringstream sin{"123456"};

        REQUIRE( sin.ignore(3) ); 

        REQUIRE( sin.get() == '4' );
    }

    SECTION( "ignore all character" ) {
        istringstream sin{"123456"};

        REQUIRE( sin.ignore(numeric_limits<int>::max()) ); 

        REQUIRE( sin.get() == EOF );

        REQUIRE_FALSE ( sin.ignore(1) );
    }

}

TEST_CASE( "peek", "[std] [istream] [input]" ) {

     SECTION( "peek one character" ) {
        istringstream sin{"ABCDEFG"};

        REQUIRE( sin.peek() == 'A' ); 
    }

    SECTION( "peek when next character is new line" ) {
        istringstream sin{"\nABCDEFG"};

        REQUIRE( sin.peek() == '\n' ); 
    }

    SECTION( "peek when next character is eof" ) {
        istringstream sin;

        REQUIRE( sin.peek() == EOF ); 
    }
    
}

TEST_CASE( "putback", "[std] [istream] [input]" ) {

    SECTION( "fails for input only stream" ) {
        istringstream sin{"ABCDEFG"};

        sin.get();

        REQUIRE_FALSE( sin.putback('a') );
    }

    SECTION( "succeedes for input only stream when put back character is not different from character extracted" ) {
        istringstream sin{"ABCDEFG"};

        REQUIRE( sin.get() == 'A' );
        REQUIRE( sin.putback('A') );
        REQUIRE( sin.get() == 'A' );
    }

    SECTION( "replace first character in the stream" ) {
        stringstream sin{"ABCDEFG"};

        sin.get();

        REQUIRE( sin.putback('a') );
        REQUIRE( sin.get() == 'a' );
        REQUIRE( sin.get() == 'B' );
    }

    SECTION( "fails if no character was retrieved prior" ) {
        stringstream sin{"ABCDEFG"};

        REQUIRE_FALSE( sin.putback('a') );
    }
    
}

TEST_CASE( "read", "[std] [istream] [input]" ) {

    SECTION( "read one character" ) {
        istringstream sin{"12345"};
        
        char ch = '\0';
        REQUIRE( sin.read(&ch, 1) );

        REQUIRE( 1 == sin.gcount() );
        REQUIRE( ch == '1' );
    }

    SECTION( "read exact" ) {
        istringstream sin{"12345"};
        
        const int count = 5;
        const char non_null_char = 'Z';
        char buffer[count + 1];
        buffer[count] = non_null_char;

        REQUIRE( sin.read(buffer, count) );

        REQUIRE( count == sin.gcount() );
        REQUIRE( buffer[count] == non_null_char );

        buffer[count] = '\0';
        REQUIRE( buffer == string{"12345"} );
    }

    SECTION( "try to read more than in the stream" ) {
        istringstream sin{"12345"};
        
        const int count = 10;
        char buffer[count + 1];

        REQUIRE_FALSE( sin.read(buffer, count) );

        REQUIRE( sin.gcount() == 5 );

        buffer[5] = '\0';
        REQUIRE( buffer == string{"12345"} );
    }

    SECTION( "try to read from empty stream" ) {
        istringstream sin;
        
        char buffer[1];

        REQUIRE_FALSE( sin.read(buffer, 1) );

        REQUIRE( sin.gcount() == 0 );
    }

}

TEST_CASE( "readsome", "[std] [istream] [input]" ) {

    SECTION( "read one character if available in internal buffer" ) {
        istringstream sin{"ABC"};
        REQUIRE( sin.rdbuf()->in_avail() > 0 );
        
        char ch = '\0';

        REQUIRE( sin.readsome(&ch, 1) == 1 );

        REQUIRE( ch == 'A' );
    }

    SECTION( "try to read more characters that area available" ) {
        istringstream sin{"ABC"};
        REQUIRE( sin.rdbuf()->in_avail() > 0 );
        
        const int count = 10;
        char buffer[count];

        REQUIRE( sin.readsome(buffer, count) == 3 );

        buffer[3] = '\0';

        REQUIRE( buffer == string{"ABC"} );
    }

    SECTION( "try to readsome from empty stream" ) {
        istringstream sin;
        REQUIRE( sin.rdbuf()->in_avail() == 0 );
        
        const int count = 10;
        char buffer[count];

        REQUIRE( sin.readsome(buffer, count) == 0 );
        REQUIRE( sin );

        REQUIRE( sin.readsome(buffer, count) == 0 );
        REQUIRE( sin );
    }

}

TEST_CASE( "unget", "[std] [istream] [input]" ) {

    SECTION( "unget read character" ) {
        istringstream sin{"ABCDEFG"};

        REQUIRE( sin.get() == 'A' );
        REQUIRE( sin.unget() );
        REQUIRE( sin.get() == 'A' );
    }

    SECTION( "unget fails after eof" ) {
        istringstream sin{"A"};

        REQUIRE( sin.get() == 'A' );
        REQUIRE( sin.get() == EOF );
        REQUIRE_FALSE( sin.unget() );
    }

    SECTION( "unget last character" ) {
        istringstream sin{"ABC"};

        REQUIRE( sin.get() == 'A' );
        REQUIRE( sin.get() == 'B' );

        REQUIRE( sin.get() == 'C' );
        REQUIRE( sin.unget() );
        REQUIRE( sin.get() == 'C' );
    }

}
