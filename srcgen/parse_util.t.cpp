#include <catch.hpp>
#include <parse_util.h>

using namespace std;

namespace srcgen {

TEST_CASE( "find_delimiters" ) {
    
    SECTION( "same delimiters" ) {
        const string str{"|some value|"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '|' 
                            , '|' 
                        );
        
        REQUIRE( cend(str) != pr.first );
        REQUIRE( '|' == *pr.first );
        
        REQUIRE( cend(str) != pr.second );
        REQUIRE( '|' == *pr.second );

    } 

    SECTION( "different delimiters" ) {
        const string str{"[some value]"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( cend(str) != pr.first );
        REQUIRE( '[' == *pr.first );
        
        REQUIRE( cend(str) != pr.second );
        REQUIRE( ']' == *pr.second );
    }

    SECTION( "only first delimiter found" ) {
        const string str{"[some value"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( cend(str) != pr.first );
        REQUIRE( '[' == *pr.first );

        REQUIRE( cend(str) == pr.second );
    }

    SECTION( "no delimiters found" ) {
        const string str{"some value"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( cend(str) == pr.first );
        REQUIRE( cend(str) == pr.second );
    }

    SECTION( "there is only second delimiter and it is ignored" ) {
        const string str{"some value]"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( cend(str) == pr.first );
        REQUIRE( cend(str) == pr.second );
    }

    SECTION( "delimiters are in the middle of the string" ) {
        const string str{"bla begin \"some value\" bla end"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '"' 
                            , '"' 
                        );
        
        REQUIRE( cend(str) != pr.first );
        REQUIRE( '"' == *pr.first );

        REQUIRE( cend(str) != pr.second );
        REQUIRE( '"' == *pr.second );
    }

}

} // srcgen
