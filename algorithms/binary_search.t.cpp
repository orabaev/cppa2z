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


