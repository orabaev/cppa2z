#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

using namespace std;

TEST_CASE( "adjacent_find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "two consecutive elements found in the range at position 2" ) {
        const vector<int> vec{1, 2, 3, 3, 5, 6, 7};

        const auto it = adjacent_find(cbegin(vec), cend(vec));

        REQUIRE( it != cend(vec) );
        const auto found_at_pos = distance(cbegin(vec), it);
        REQUIRE( found_at_pos == 2 );
    } 

    SECTION( "using predicates; two consecutive upper case characters found in the range at position 3" ) {
        const string str{"aBcDEfg"};
        auto both_upper = [](char x, char y) { return isupper(x) && isupper(y); };

        const auto it = adjacent_find(cbegin(str), cend(str), both_upper);

        REQUIRE( it != cend(str) );
        const auto found_at_pos = distance(cbegin(str), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "all_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicates; all elements in the range match" ) {
        const vector<int> vec{2, 4, 6, 8, 10, 12, 14};
        auto is_even = [](int i) { return i % 2 == 0; };

        REQUIRE( all_of(cbegin(vec), cend(vec), is_even) );
    } 

}

TEST_CASE( "any_of", "[std] [algorithm] [non modifying] [not none_of]" ) {
    
    SECTION( "some of the elements in the range match" ) {
        const vector<int> vec{1, 2, 3, 2, 5, 6, 7};
        auto is_one = [](int i) { return i == 1; };

        REQUIRE( any_of(cbegin(vec), cbegin(vec), is_one) );
    } 

}

TEST_CASE( "count", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "returns number of 1s in the range" ) {
        const vector<int> vec{1, 1, 2, 5, 1, 1, 6};

        REQUIRE( 4 == count(cbegin(vec), cend(vec), 1) );
    } 

}

TEST_CASE( "count_if", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicates; returns number of even numbers in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5, 6, 7};
        auto is_even = [](int i) { return i % 2 == 0; };

        REQUIRE( 3 == count_if(cbegin(vec), cend(vec), is_even) );
    }

}

TEST_CASE( "equal", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "start from the begining; two ranges are equal; comparing vector and list" ) {
        const vector<int> vec{1, 2, 3, 4, 5, 6, 7};
        const list<int>   lst{1, 2, 3, 4, 5, 6, 7};

        REQUIRE( equal(cbegin(vec), cend(vec), cbegin(lst)) );
    }

    SECTION( "start from the 3rd element; two ranges are equal; comparing vector and list" ) {
        const vector<int> vec{-1, 0, 1, 2, 3, 4, 5};
        const list<int>   lst{1, 2, 3, 4, 5, 6, 7};

        REQUIRE( equal(cbegin(vec) + 2, cend(vec), cbegin(lst)) );
    }

    SECTION( "using reverse iterator; two ranges are equal" ) {
        const vector<int> vec1{1, 2, 3, 4, 5, 6, 7};
        const vector<int> vec2{7, 6, 5, 4, 3, 2, 1};
        const auto reverse_iterator = crbegin(vec2); 

        REQUIRE( equal(cbegin(vec1), cend(vec1), reverse_iterator) );
    }

    SECTION( "using predicates; two ranges are equal" ) {
        const string str1{"aBCd1fG"};
        const string str2{"AbCD1Fg"};
        auto case_insensitive_compare = [](char x, char y) { return toupper(x) == toupper(y); };

        REQUIRE( equal(cbegin(str1), cend(str1), cbegin(str2), case_insensitive_compare) );
    }

}

