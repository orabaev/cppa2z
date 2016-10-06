#include <catch.hpp>
#include <algorithm>
#include <vector>

TEST_CASE( "adjacent_find", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "two consecutive elements found in the range at position 2" ) {
        std::vector<int> vec{1,2,3,3,5,6,7};
        auto it = std::adjacent_find(vec.begin(), vec.end());
        REQUIRE( it != vec.end() );
        auto found_at_pos = std::distance(vec.begin(), it);
        REQUIRE( found_at_pos == 2 );
    } 

    SECTION( "using predicates; two consecutive upper case characters found in the range at position 3" ) {
        std::vector<char> vec{'a','B','c','D','E','f','g'};
        auto both_upper = [](char x, char y) { return std::isupper(x) && std::isupper(y); };
        auto it = std::adjacent_find(vec.begin(), vec.end(), both_upper);
        REQUIRE( it != vec.end() );
        auto found_at_pos = std::distance(vec.begin(), it);
        REQUIRE( found_at_pos == 3 );
    }

}

TEST_CASE( "all_of", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "all elements in the range match" ) {
        std::vector<int> vec{2,4,6,8,10,12,14};
        auto is_even = [](int i) { return i % 2 == 0; };
        REQUIRE( std::all_of(vec.begin(), vec.end(), is_even) );
    } 

    SECTION( "not all elements in the range match" ) {
        std::vector<int> vec{1,1,0,1,1,1};
        auto is_one = [](int i) { return i == 1; };
        REQUIRE_FALSE( std::all_of(vec.begin(), vec.end(), is_one) );
    } 

}

TEST_CASE( "any_of", "[std] [algorithm] [non modifying] [not none_of]" ) {
    
    auto is_one = [](int i) { return i == 1; };
    auto is_two = [](int i) { return i == 2; };

    SECTION( "some of the elements in the range match" ) {
        std::vector<int> vec{1,2,3,2,5,6,7};
        REQUIRE( std::any_of(vec.begin(), vec.end(), is_one) );
        REQUIRE( std::any_of(vec.begin(), vec.end(), is_two) );
    } 

    SECTION( "none of the elements in the range match" ) {
        std::vector<int> vec{1,1,3,3,5,6,7};
        REQUIRE_FALSE( std::any_of(vec.begin(), vec.end(), is_two) );
    } 

}

TEST_CASE( "count", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "returns number of 1s in the range" ) {
        std::vector<int> vec{1,1,2,5,1,1,6};
        REQUIRE( 4 == std::count(vec.begin(), vec.end(), 1) );
    } 

}

TEST_CASE( "count_if", "[std] [algorithm] [non modifying]" ) {
    
    SECTION( "using predicates; returns number of even numbers in the range" ) {
        std::vector<int> vec{1,2,3,4,5,6,7};
        auto is_even = [](int i) { return i % 2 == 0; };
        REQUIRE( 3 == std::count_if(vec.begin(), vec.end(), is_even) );
    }

}

