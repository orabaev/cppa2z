#include <catch.hpp>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE( "is_sorted", "[std] [algorithm] [sorting]" ) {
    
    SECTION( "the range is sorted" ) {
        const vector<int> vec{0, 1, 2, 2, 3, 4, 4};

        REQUIRE( is_sorted(cbegin(vec), cend(vec)) );
    } 

    SECTION( "the range is not sorted" ) {
        const vector<int> vec{0, 1, 2, 1000, 3, 4, 4};

        REQUIRE_FALSE( is_sorted(cbegin(vec), cend(vec)) );
    } 

    SECTION( "the range is sorted in descending order" ) {
        const vector<int> vec{5, 4, 3, 2, 1};

        REQUIRE( is_sorted(cbegin(vec), cend(vec), greater<int>()) );
    }

}

TEST_CASE( "is_sorted_unti", "[std] [algorithm] [sorting]" ) {
    
    SECTION( "the range is sorted until 3rd element" ) {
        const vector<int> vec{5, 6, 7, 2, 3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        auto last_pos = distance(cbegin(vec), last_it);
        REQUIRE( 3 == last_pos );
    } 

    SECTION( "the range is fully sorted" ) {
        const vector<int> vec{0, 1, 1, 2, 3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        REQUIRE( cend(vec) == last_it );
    }

    SECTION( "the range is not sorted until" ) {
        const vector<int> vec{5, 1, 2, 1000, 3, 4, 4};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec));
        
        CHECK ( ++cbegin(vec) == last_it );
    } 

    SECTION( "the range is sorted until in descending order" ) {
        const vector<int> vec{5, 4, 3, 2, 10, 4, 9};

        const auto last_it = is_sorted_until(cbegin(vec), cend(vec), greater<int>());

        auto last_pos = distance(cbegin(vec), last_it);
        REQUIRE( 4 == last_pos );
    }

}


