#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "binary_search", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "find element in the sorted range" ) {
        const vector<int> vec{0, 1, 2, 3, 4, 5, 6};

        REQUIRE( binary_search(cbegin(vec), cend(vec), 0) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 4) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 6) );
    } 

    SECTION( "find element in the partially sorted range" ) {
        const vector<int> vec{0, 1, 2, 3, 4,   6, 5};

        REQUIRE( binary_search(cbegin(vec), cend(vec)+4, 3) );
    }

    SECTION( "element not found in the sorted range" ) {
        const vector<int> vec{0, 1, 2, 3, 4, 5, 6};

        REQUIRE_FALSE( binary_search(cbegin(vec), cend(vec), 10) );
    } 

    SECTION( "find element in the descending order sorted range" ) {
        const vector<int> vec{6, 5, 4, 3, 2, 1, 0};

        REQUIRE( binary_search(cbegin(vec), cend(vec), 0, greater<int>()) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 4, greater<int>()) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 6, greater<int>()) );
    }

}

TEST_CASE( "equal_range", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "find all elements equel to 2 in the sorted range" ) {
        const vector<int> vec{0, 1,   2,2,2,2,2,2,   4, 5, 6};

        const auto pr = equal_range(cbegin(vec), cend(vec), 2);

        REQUIRE( *pr.first  == 2);
        REQUIRE( *pr.second == 4);
        REQUIRE( distance(pr.second, pr.first) == -6);
    } 

    SECTION( "elements equel to 2 not found in the sorted range" ) {
        const vector<int> vec{0, 0, 1, 1, 4, 5, 6};

        const auto pr = equal_range(cbegin(vec), cend(vec), 2);

        bool not_found = pr.first == pr.second;
        REQUIRE( not_found );
    } 

    SECTION( "find all elements equel to 2 in the descending order sorted range" ) {
        const vector<int> vec{6, 5, 4,   2,2,2,   1, 0};

        const auto pr = equal_range(
                              cbegin(vec)
                            , cend(vec)
                            , 2
                            , greater<int>()
                        );

        REQUIRE( *pr.first  == 2);
        REQUIRE( *pr.second == 1);
        REQUIRE( distance(pr.second, pr.first) == -3);
    } 

}

TEST_CASE( "lower_bound", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "find first elements equel to 2 in the sorted range" ) {
        const vector<int> vec{0, 1,   2,   2, 4, 5, 6};

        auto it = lower_bound(cbegin(vec), cend(vec), 2);

        REQUIRE( *it == 2);
        REQUIRE( *prev(it) == 1);
    } 

    SECTION( "elements equel to 2 is not found in the sorted range" ) {
        const vector<int> vec{0, 1, 1, 3, 4, 5, 6};

        const auto it = lower_bound(cbegin(vec), cend(vec), 2);

        REQUIRE( *it == 3 );
    }

    SECTION( "find first elements equel to 2 in the descending order sorted range" ) {
        const vector<int> vec{6, 5, 4,   2, 2,   1, 0};

        auto it = lower_bound(
                        cbegin(vec)
                      , cend(vec)
                      , 2
                      , greater<int>()
                  );

        REQUIRE( *it == 2);
        REQUIRE( *prev(it) == 4 );
    } 

}

TEST_CASE( "upper_bound", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "find first element greater than 2 in the sorted range" ) {
        const vector<int> vec{0, 1, 2, 2,   4,   5, 6};

        auto it = upper_bound(cbegin(vec), cend(vec), 2);

        REQUIRE( *it == 4);
        REQUIRE( *prev(it) == 2);
    } 

    SECTION( "no elements greater than 2 found in the sorted range" ) {
        const vector<int> vec{0, 0, 1, 1, 2, 2, 2};

        const auto it = upper_bound(cbegin(vec), cend(vec), 2);

        REQUIRE( cend(vec) == it );
    }

    SECTION( "find element less than 2 in the descending order sorted range" ) {
        const vector<int> vec{6, 5,   4,   2, 2, 1, 0};

        auto it = upper_bound(
                        cbegin(vec)
                      , cend(vec)
                      , 2
                      , greater<int>()
                  );

        REQUIRE( *it == 1);
        REQUIRE( *prev(it) == 2);
    } 

}
