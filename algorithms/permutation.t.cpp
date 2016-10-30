#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "is_permutation", "[std] [algorithm] [permutation]" ) {
    
    SECTION( "determine if one range is permutation of another" ) {
        const vector<int> vec1{0, 1, 2, 3};
        const vector<int> vec2{2, 1, 0, 3};
        
        const bool is_perm = is_permutation(
                                 cbegin(vec1)
                               , cend(vec1)
                               , cbegin(vec2)
                             );
                  
        REQUIRE( is_perm ); 

    } 

    SECTION( "one range is permutation of another using case insensetive compare" ) {
        const string str1{"abcde"};
        const string str2{"CeBDa"};
        
        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };
        
        const bool is_perm = is_permutation(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , case_insensitive_compare 
                             );
                  
        REQUIRE( is_perm ); 

    } 

    SECTION( "one range is not permutation of another" ) {
        const vector<int> vec1{0, 1, 2, 3};
        const vector<int> vec2{2, 1, 0, 3};
        
        const bool is_perm = is_permutation(
                                 cbegin(vec1)
                               , cend(vec1)
                               , cbegin(vec2)
                               , cend(vec2) - 1
                             );
                  
        REQUIRE_FALSE( is_perm ); 

    } 

    SECTION( "one range is another using case insensetive compare" ) {
        const string str1{"abcde"};
        const string str2{"CebDa"};
        
        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };
        
        const bool is_perm = is_permutation(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , case_insensitive_compare 
                             );
                  
        REQUIRE( is_perm ); 

    }

}

TEST_CASE( "lexicographical_compare", "[std] [algorithm] [permutation]" ) {
    
    SECTION( "compares equal sized ranges lexicographicaly" ) {
        const string str1{"abcd e"};
        const string str2{"abcd z"};

        const bool is_less = lexicographical_compare(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , cend(str2)
                             );

        REQUIRE( is_less );
    } 

    SECTION( "compares non equal sized ranges lexicographicaly" ) {
        const string str1{"abcd"};
        const string str2{"ef"};

        const bool is_less = lexicographical_compare(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , cend(str2)
                             );

        REQUIRE( is_less );
    }

    SECTION( "case insensitive compares ranges lexicographicaly ignoring cases" ) {
        const string str1{"abcd"};
        const string str2{"ef"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) < toupper(y); };

        const bool is_less = lexicographical_compare(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , cend(str2)
                               , case_insensitive_compare 
                             );

        REQUIRE( is_less );
    }

    SECTION( "case insensitive compares ranges lexicographicaly ignoring cases 2" ) {
        const string str1{"abcde"};
        const string str2{"abcde"};

        const bool is_less = lexicographical_compare(
                                 cbegin(str1)
                               , cend(str1)
                               , cbegin(str2)
                               , cend(str2)
                             );

        REQUIRE_FALSE( is_less );
    }

}

TEST_CASE( "next_permutation", "[std] [algorithm] [permutation]" ) {
    
    SECTION( "generates next lexicographicaly ordered permutation" ) {
              vector<int>   vec{0, 1, 2};
        const vector<int> perm1{0, 2, 1};
        const vector<int> perm2{1, 0, 2};
        const vector<int> perm3{1, 2, 0};
        const vector<int> perm4{2, 0, 1};
        const vector<int> perm5{2, 1, 0};
        const vector<int> perm6{0, 1, 2};


        REQUIRE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm1 == vec );

        REQUIRE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm2 == vec );

        REQUIRE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm3 == vec );

        REQUIRE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm4 == vec );

        REQUIRE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm5 == vec );

        REQUIRE_FALSE( next_permutation(begin(vec), end(vec)) );
        REQUIRE( perm6 == vec );
    } 

    SECTION( "generates next lexicographicaly ordered permutation using case insensitive compare" ) {
              string    str{"aBc"};
        const string  perm1{"acB"};
        const string  perm2{"Bac"};
        const string  perm3{"Bca"};
        const string  perm4{"caB"};
        const string  perm5{"cBa"};
        const string  perm6{"aBc"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) < toupper(y); };

        REQUIRE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm1 == str );

        REQUIRE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm2 == str );

        REQUIRE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm3 == str );

        REQUIRE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm4 == str );

        REQUIRE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm5 == str );

        REQUIRE_FALSE( next_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm6 == str );
    }

}

TEST_CASE( "prev_permutation", "[std] [algorithm] [permutation]" ) {
    
    SECTION( "generates prev lexicographicaly ordered permutation" ) {
              vector<int>   vec{0, 1, 2};
        const vector<int> perm1{2, 1, 0};
        const vector<int> perm2{2, 0, 1};
        const vector<int> perm3{1, 2, 0};
        const vector<int> perm4{1, 0, 2};
        const vector<int> perm5{0, 2, 1};
        const vector<int> perm6{0, 1, 2};

        REQUIRE_FALSE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm1 == vec );

        REQUIRE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm2 == vec );

        REQUIRE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm3 == vec );

        REQUIRE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm4 == vec );

        REQUIRE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm5 == vec );

        REQUIRE( prev_permutation(begin(vec), end(vec)) );
        REQUIRE( perm6 == vec );
    } 

    SECTION( "generates prev lexicographicaly ordered permutation using case insensitive compare" ) {
              string    str{"aBc"};
        const string  perm1{"cBa"};
        const string  perm2{"caB"};
        const string  perm3{"Bca"};
        const string  perm4{"Bac"};
        const string  perm5{"acB"};
        const string  perm6{"aBc"};

        auto case_insensitive_compare = [](char x, char y) { return toupper(x) < toupper(y); };

        REQUIRE_FALSE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm1 == str );

        REQUIRE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm2 == str );

        REQUIRE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm3 == str );

        REQUIRE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm4 == str );

        REQUIRE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm5 == str );

        REQUIRE( prev_permutation(begin(str), end(str), case_insensitive_compare) );
        REQUIRE( perm6 == str );
    }

}
