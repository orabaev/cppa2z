// advance
// distance
// next
// prev

#include <catch.hpp>
#include <iterator>
#include <vector>

using namespace std;

TEST_CASE( "advance", "[std] [iterator] [operations]" ) {
    
    SECTION( "advance forward" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        auto it = cbegin(vec); 

        advance(it, 3);
        REQUIRE( 3 == *it );
    }

    SECTION( "advance backward" ) {
        vector<int> vec{0,  1, 2, 3, 4, 5};

        auto it = cend(vec); 

        advance(it, -6);
        REQUIRE( 0 == *it );
    }

}

TEST_CASE( "distance", "[std] [iterator] [operations]" ) {
    
    SECTION( "distance from begining to end" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        const auto val = distance(cbegin(vec), cend(vec));

        REQUIRE( vec.size() == val );
    }

    SECTION( "distance from end to beggining" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        const auto val = distance(cend(vec), cbegin(vec));

        REQUIRE( -vec.size() == val );
    }

    SECTION( "distance between elements" ) {
        const vector<int> vec{0,   1, 2,  3,  4,   5};

        auto it_first = cbegin(vec) + 1;
        auto it_last  = cbegin(vec) + 4;

        const auto val = distance(it_first, it_last);

        REQUIRE( 3 == val );
    }

}
