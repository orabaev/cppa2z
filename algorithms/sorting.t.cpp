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

TEST_CASE( "nth_element", "[std] [algorithm] [sorting]" ) {
    
     SECTION( "set nth element in its sorted position and partition the range "
              " with first group LESS than nth element" ) {
        vector<int> vec{4, 2, 5, 3, 1, 0, 2};
        
        auto nth = begin(vec) + 2;
        REQUIRE ( 5 == *nth );

        nth_element(begin(vec), nth, end(vec));

        REQUIRE ( 2 == *nth );
        
        auto less_than_nth = [&nth](int x) { return x < *nth; };
        
        REQUIRE( all_of(begin(vec), nth, less_than_nth) );
        REQUIRE( none_of(nth, end(vec), less_than_nth) );
    } 

    SECTION( "set nth element in its sorted position and partition the range "
              " with first group GREATER than nth element" ) {
        vector<int> vec{4, 2, 5, 3, 1, 0, 2};
        
        auto nth = begin(vec) + 2;
        REQUIRE ( 5 == *nth );

        nth_element(begin(vec), nth, end(vec), greater<int>());

        REQUIRE ( 3 == *nth );
        
        auto greater_than_nth = [&nth](int x) { return x > *nth; };
        
        REQUIRE( all_of(begin(vec), nth, greater_than_nth) );
        REQUIRE( none_of(nth, end(vec), greater_than_nth) );
    } 

}