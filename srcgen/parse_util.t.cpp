#include <catch.hpp>
#include <parse_util.h>
#include <sstream>

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

TEST_CASE( "copy_all_or_after" ) {
    
    SECTION( "copy when delimiter was found" ) {
        const string     from{"istringstream.operator="};
              string       to; 
        const string expected{"operator="};
        
        copy_all_or_after(
              cbegin(from)
            , cend(from)
            , '.'
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "copy when delimiter was not found" ) {
        const string     from{"operator="};
              string       to; 
        const string expected{"operator="};
        
        copy_all_or_after(
              cbegin(from)
            , cend(from)
            , '.'
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    }

    SECTION( "empty string" ) {
        const string     from;
              string       to; 
        const string expected;
        
        copy_all_or_after(
              cbegin(from)
            , cend(from)
            , '.'
            , back_inserter(to)
        );

        REQUIRE( expected == to );
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
        const string    str{"abc|HELLO|def|WORLD|12345|C++|"};
        vector<string>  vec;

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

TEST_CASE( "is_test_case" ) {
    
    SECTION( "found at the begining of the line" ) {
        const string line_of_code{"TEST_CASE( \"testcase\" )"};

        REQUIRE( is_test_case(line_of_code) );
    }

    SECTION( "found at the begining of the line spaces ignored" ) {
        const string line_of_code{"     TEST_CASE( \"testcase\" )"};

        REQUIRE( is_test_case(line_of_code) );
    }

    SECTION( "not found" ) {
        const string line_of_code{"int i = 10;"};

        REQUIRE_FALSE( is_test_case(line_of_code) );
    }

    SECTION( "not found at the begining" ) {
        const string line_of_code{"////TEST_CASE("};

        REQUIRE_FALSE( is_test_case(line_of_code) );
    }

    SECTION( "empty string" ) {
        const string line_of_code;

        REQUIRE_FALSE( is_test_case(line_of_code) );
    }


}

TEST_CASE( "get_test_case_name" ) {
    const string expected{"testcase"};;    
    const string line_of_code{"TEST_CASE( \"testcase\" )"};

    auto test_case_name = get_test_case_name(line_of_code); 

    REQUIRE( expected == test_case_name );
}

TEST_CASE( "extract_test_case_lines" ) {
    stringstream sio;  

    sio << "#include <iostream> \n"
        << "\n"
        << "\n"
        << "bla bla\n"
        << "bla bla\n"
        << "TEST_CASE( \"adjacent_find\", \"[std] [algorithm] [non modifying]\" ) {\n"
        << "bla bla\n"
        << "bla bla\n"
        << "bla bla\n"
        << "bla bla\n"
        << "TEST_CASE( \"count\", \"[std] [algorithm] [non modifying]\" ) {\n"
        << "bla bla\n"
        << "bla bla\n"
        << "bla bla\n"
        << "\n"
        << "\n"
        << "TEST_CASE( \"count_if\", \"[std] [algorithm] [non modifying]\" ) {\n"
        << "\n"
        << "\n"
        << "\n"
        << endl;

    auto vec = extract_test_case_lines(sio);
    
    REQUIRE ( 3 == vec.size() );

    REQUIRE ( 6 == vec[0].first );
    REQUIRE ( "adjacent_find" == vec[0].second );

    REQUIRE ( 11 == vec[1].first );
    REQUIRE ( "count" == vec[1].second );

    REQUIRE ( 17 == vec[2].first );
    REQUIRE ( "count_if" == vec[2].second );
}

} // namespace srcgen
