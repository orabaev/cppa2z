#include <catch.hpp>
#include <algorithm>
#include <vector>

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

