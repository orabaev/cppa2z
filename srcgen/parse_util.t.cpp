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

    SECTION( "delimiters are found next to each other" ) {
        const string str{"bla begin [] bla end"};

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
}

TEST_CASE( "copy_delimited" ) {
    
    SECTION( "value copied" ) {
        const string     from{"abc|HELLO|def"};
              string       to;
        const string expected{"HELLO"};

        const auto pr = copy_delimited(
                              cbegin(from)
                            , cend(from)
                            , '|' 
                            , '|' 
                            , back_inserter(to)
                        );
        
        REQUIRE( pr.first );
        REQUIRE( 'd' == *pr.second );
        
        REQUIRE( expected == to );
    } 

    SECTION( "empty value copied" ) {
        const string     from{"abc||def"};
              string       to;

        const auto pr = copy_delimited(
                              cbegin(from)
                            , cend(from)
                            , '|' 
                            , '|' 
                            , back_inserter(to)
                        );
        
        REQUIRE( pr.first );
        REQUIRE( 'd' == *pr.second );
        
        REQUIRE( to.empty() );
    }

    SECTION( "nothing copied" ) {
        const string     from{"abcdef"};
              string       to;

        const auto pr = copy_delimited(
                              cbegin(from)
                            , cend(from)
                            , '|' 
                            , '|' 
                            , back_inserter(to)
                        );
        
        REQUIRE_FALSE( pr.first );
        REQUIRE( cend(from) == pr.second );
        
        REQUIRE( to.empty() );
    }

    SECTION( "several delimited strings" ) {
        const string     from{"ab[HELLO ]cd|WORLD|ef"};
              string       to;

        auto pr = copy_delimited(
                      cbegin(from)
                    , cend(from)
                    , '[' 
                    , ']' 
                    , back_inserter(to)
                  );
    
        REQUIRE( pr.first );
        REQUIRE( "HELLO " == to );

        pr = copy_delimited(
                  cbegin(from)
                , cend(from)
                , '|' 
                , '|' 
                , back_inserter(to)
             );
       
          
        REQUIRE( pr.first );
        REQUIRE( "HELLO WORLD" == to );
         
    }

}

TEST_CASE( "extract_delimited" ) {
    
    SECTION( "single delimited element" ) {
        const string     str{"abc|HELLO|def"};
        vector<string>   vec;

        bool ret = extract_delimited(
                         cbegin(str)
                       , cend(str)
                       , '|' 
                       , '|' 
                       , vec
                   );
    
        REQUIRE( ret ); 
        REQUIRE( 1 == vec.size() ); 
        REQUIRE( "HELLO" == vec[0] ); 
    } 

    SECTION( "single delimited element" ) {
        const string     str{"abc|HELLO|def|WORLD|12345|C++|"};
        vector<string>   vec;

        bool ret = extract_delimited(
                         cbegin(str)
                       , cend(str)
                       , '|' 
                       , '|' 
                       , vec
                   );
    
        REQUIRE( ret ); 
        REQUIRE( 3 == vec.size() ); 
        REQUIRE( "HELLO" == vec[0] ); 
        REQUIRE( "WORLD" == vec[1] ); 
        REQUIRE( "C++"   == vec[2] ); 
    }

    SECTION( "no delimited element" ) {
        const string     str{"abc|HELLO|def|WORLD|12345|C++|"};
        vector<string>   vec;

        bool ret = extract_delimited(
                         cbegin(str)
                       , cend(str)
                       , '[' 
                       , ']' 
                       , vec
                   );
    
        REQUIRE_FALSE( ret ); 
        REQUIRE( vec.empty() ); 
    }

}

} // namespace srcgen
