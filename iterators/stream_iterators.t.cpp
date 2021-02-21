// istream_iterator
// istreambuf_iterator
// ostream_iterator
// ostreambuf_iterator

#include <catch.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

using namespace std;

TEST_CASE( "istream_iterator", "[std] [iterator] [stream]" ) {
    
    SECTION( "read and sum numbers from string stream" ) {
        istringstream sin{"1 2 3 4 5"};
        const int expected = 1 + 2 + 3 + 4 + 5;

        const int sum = accumulate(
                              istream_iterator<int>(sin)
                            , istream_iterator<int>()
                            , 0
                        );  

        REQUIRE( sum == expected );
    } 

    SECTION( "copy characters from istringstream skipping white spaces" ) {
              istringstream sin{"1 2 3 4 5"};
              string        str; 
        const string        expected{"12345"};

        copy(
              istream_iterator<char>(sin)
            , istream_iterator<char>()
            , back_inserter(str)
        );

        REQUIRE( str == expected );
    } 
   
}

TEST_CASE( "istreambuf_iterator", "[std] [iterator] [stream]" ) {
    
    SECTION( "copy characters from istringstream" ) {
              istringstream sin{"1 2 3 4 5"};
              string        str; 
        const string        expected{"1 2 3 4 5"};

        copy(
              istreambuf_iterator<char>(sin)
            , istreambuf_iterator<char>()
            , back_inserter(str)
        );

        REQUIRE( str == expected );
    }

}

TEST_CASE( "ostream_iterator", "[std] [iterator] [stream]" ) {
    
    SECTION( "write delimited elements to string stream" ) {
        const vector<int> vec{1, 2, 3, 4, 5};
        const string expected{"1->2->3->4->5->"};

        ostringstream sout; 
        const string  delimiter{"->"};

        auto output_it = ostream_iterator<int>(sout, "->"); 
        
        copy(cbegin(vec), cend(vec), output_it);

        REQUIRE( sout.str() == expected );
    } 
   
}

TEST_CASE( "ostreambuf_iterator", "[std] [iterator] [stream]" ) {

    SECTION( "copy sting to string stream using ostreambuf iterator" ) {
        const string str{"Hello C++"};
        
        ostringstream sout; 
        copy(cbegin(str), cend(str), ostreambuf_iterator<char>(sout));

        REQUIRE( sout.str() == str );

    }

    SECTION( "copy values to string stream using two ostreambuf iterator" ) {
        ostringstream sout; 
        auto output_it1 = ostreambuf_iterator<char>(sout);
        auto output_it2 = ostreambuf_iterator<char>(sout);
        
        *output_it1 = 'a';
        REQUIRE( sout.str() == "a" );

        *output_it2 = 'b';
        REQUIRE( sout.str() == "ab" );

        *output_it1 = 'c';
        REQUIRE( sout.str() == "abc" );

        *output_it2 = 'd';
        REQUIRE( sout.str() == "abcd" );
    } 
 
}
