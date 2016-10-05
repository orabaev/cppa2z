#include <catch.hpp>
#include <algorithm>
#include <vector>

TEST_CASE( "all_of", "[std] [algorithm]" ) {
    
    SECTION( "all elements in the range match" ) {
        std::vector<int> vec{2,4,6,8,10};
        auto is_even = [](int i) { return i % 2 == 0; };

        REQUIRE( std::all_of(vec.begin(), vec.end(), is_even) );
    } 

    SECTION( "not all elements in the range match" ) {
        std::vector<int> vec{1,1,0,1,1};
        auto is_one = [](int i) { return i == 1; };

        REQUIRE_FALSE( std::all_of(vec.begin(), vec.end(), is_one) );
    } 

}

