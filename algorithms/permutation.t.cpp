#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "is_permutation", "[std] [algorithm] [sorting] [binary search]" ) {
    
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

TEST_CASE( "lexicographical_compare", "[std] [algorithm] [non modifying]" ) {
    
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

    SECTION( "compares  equal sized ranges" ) {
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


