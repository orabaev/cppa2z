// istream_iterator
// istreambuf_iterator
// ostream_iterator
// ostreambuf_iterator

#include <catch.hpp>
#include <algorithm>
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

        REQUIRE( expected == sum );
    } 
   
}

TEST_CASE( "istreambuf_iterator", "[std] [iterator] [stream]" ) {
    
    SECTION( "demonstrate parallel increment of two istreambuf iterators" ) {
        istringstream sin("a b");
        istreambuf_iterator<char> input_it1(sin);
        istreambuf_iterator<char> input_it2(sin);

        REQUIRE( *input_it1 == 'a' );
        REQUIRE( *input_it2 == 'a' );

        ++input_it1;
        REQUIRE( *input_it1 == ' ' );
        REQUIRE( *input_it2 == 'a' );

        ++input_it2;
        REQUIRE( *input_it1 == ' ' );
        REQUIRE( *input_it2 == 'b' );
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

        REQUIRE( expected == sout.str() );
    } 
   
}

TEST_CASE( "ostreambuf_iterator", "[std] [iterator] [stream]" ) {

    SECTION( "copy elements to string stream using two ostreambuf iterator" ) {
        const string str{"Hello C++"};
        
        ostringstream sout; 

        auto output_it1 = ostreambuf_iterator<char>(sout);
        auto output_it2 = ostreambuf_iterator<char>(sout);
        
        *output_it1 = 'a';
        REQUIRE( "a" == sout.str() );

        *output_it2 = 'b';
        REQUIRE( "ab" == sout.str() );

        *output_it1 = 'c';
        REQUIRE( "abc" == sout.str() );

        *output_it2 = 'd';
        REQUIRE( "abcd" == sout.str() );
    } 
 
}
