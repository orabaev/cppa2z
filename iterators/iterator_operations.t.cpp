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
        vector<int> vec{0, 1, 2,  3,  4, 5};

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
