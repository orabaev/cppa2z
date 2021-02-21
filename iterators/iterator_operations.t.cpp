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
        REQUIRE( *it == 3 );
    }

    SECTION( "advance backward" ) {
        vector<int> vec{0,  1, 2, 3, 4, 5};

        auto it = cend(vec); 

        advance(it, -6);
        REQUIRE( *it == 0 );
    }

}

TEST_CASE( "distance", "[std] [iterator] [operations]" ) {
    
    SECTION( "distance from begining to end" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        const auto val = distance(cbegin(vec), cend(vec));

        REQUIRE( val == vec.size() );
    }

    SECTION( "distance from end to beggining" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        const auto val = distance(cend(vec), cbegin(vec));

        REQUIRE( val == -vec.size() );
    }

    SECTION( "distance between elements" ) {
        const vector<int> vec{0,   1, 2,  3,  4,   5};

        auto it_first = cbegin(vec) + 1;
        auto it_last  = cbegin(vec) + 4;

        const auto val = distance(it_first, it_last);

        REQUIRE( val == 3 );
    }

}

TEST_CASE( "next", "[std] [iterator] [operations]" ) {
    
    SECTION( "next after begining" ) {
        const vector<int> vec{0,  1,  2, 3, 4, 5};

        const auto it = next(cbegin(vec), 1);

        REQUIRE( *it == 1 );
    }

    SECTION( "next n steps" ) {
        const vector<int> vec{0, 1, 2,  3,  4, 5};

        const auto it = next(cbegin(vec), 3);

        REQUIRE( *it == 3 );
    }

    SECTION( "next backwards" ) {
        const vector<int> vec{0, 1, 2, 3, 4,  5};

        const auto it = next(cend(vec), -1);

        REQUIRE( *it == 5 );
    }

}

TEST_CASE( "prev", "[std] [iterator] [operations]" ) {
    
    SECTION( "prev before end" ) {
        const vector<int> vec{0,  1,  2, 3, 4,  5};

        const auto it = prev(cend(vec), 1);

        REQUIRE( *it == 5 );
    }

    SECTION( "prev n steps" ) {
        const vector<int> vec{0, 1,  2,  3, 4, 5};

        const auto it = prev(cend(vec), 4);

        REQUIRE( *it == 2);
    }

    SECTION( "prev backwards" ) {
        const vector<int> vec{0,  1,  2, 3, 4, 5};

        const auto it = prev(cbegin(vec), -1);

        REQUIRE( *it == 1 );
    }

}
