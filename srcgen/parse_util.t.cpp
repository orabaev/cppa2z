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
        
        REQUIRE( pr.first != cend(str) );
        REQUIRE( *pr.first == '|' );
        
        REQUIRE( pr.second != cend(str) );
        REQUIRE( *pr.second == '|' );
    } 

    SECTION( "different delimiters" ) {
        const string str{"[some value]"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( pr.first != cend(str) );
        REQUIRE( *pr.first == '[' );
        
        REQUIRE( pr.second != cend(str) );
        REQUIRE( *pr.second == ']' );
    }

    SECTION( "only first delimiter found" ) {
        const string str{"[some value"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( pr.first != cend(str));
        REQUIRE( *pr.first == '[' );

        REQUIRE( pr.second == cend(str) );
    }

    SECTION( "no delimiters found" ) {
        const string str{"some value"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        
        REQUIRE( pr.first == cend(str) );
        REQUIRE( pr.second == cend(str) );
    }

    SECTION( "there is only second delimiter and it is ignored" ) {
        const string str{"some value]"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );
        

        REQUIRE( pr.first == cend(str) );
        REQUIRE( pr.second == cend(str) );
    }

    SECTION( "delimiters are in the middle of the string" ) {
        const string str{"bla begin \"some value\" bla end"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '"' 
                            , '"' 
                        );
        
        REQUIRE( pr.first != cend(str) );
        REQUIRE( *pr.first == '"' );

        REQUIRE( pr.second != cend(str) );
        REQUIRE( *pr.second == '"' );
    }

    SECTION( "delimiters are found next to each other" ) {
        const string str{"bla begin [] bla end"};

        const auto pr = find_delimiters(
                              cbegin(str)
                            , cend(str)
                            , '[' 
                            , ']' 
                        );


        REQUIRE( pr.first != cend(str) );
        REQUIRE( *pr.first == '[' );

        REQUIRE( pr.second != cend(str) );
        REQUIRE( *pr.second == ']' );
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

        REQUIRE( to == expected );
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

        REQUIRE( to == expected );
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

        REQUIRE( to == expected );
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
        REQUIRE( *pr.second == 'd' );
        
        REQUIRE( to == expected );
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
        REQUIRE( *pr.second == 'd' );
        
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
        REQUIRE( pr.second == cend(from) );
        
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
        REQUIRE( to == "HELLO " );

        pr = copy_delimited(
                  cbegin(from)
                , cend(from)
                , '|' 
                , '|' 
                , back_inserter(to)
             );
       
          
        REQUIRE( pr.first );
        REQUIRE( to == "HELLO WORLD" );
         
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
        REQUIRE( vec.size() == 1 ); 
        REQUIRE( vec[0] == "HELLO" ); 
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
        REQUIRE( vec.size() == 3 ); 
        REQUIRE( vec[0] == "HELLO" ); 
        REQUIRE( vec[1] == "WORLD" ); 
        REQUIRE( vec[2] == "C++"   ); 
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

    REQUIRE( test_case_name == expected );
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
    
    REQUIRE ( vec.size() == 3 );

    REQUIRE ( vec[0].first == 6 );
    REQUIRE ( vec[0].second == "adjacent_find" );

    REQUIRE ( vec[1].first == 11 );
    REQUIRE ( vec[1].second == "count" );

    REQUIRE ( vec[2].first == 17 );
    REQUIRE ( vec[2].second == "count_if" );
}

} // namespace srcgen
