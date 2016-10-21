#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "includes", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "find element in the sorted range" ) {
        const vector<int> vec{0, 1, 2, 3, 4, 5, 6};

        REQUIRE( binary_search(cbegin(vec), cend(vec), 0) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 4) );
        REQUIRE( binary_search(cbegin(vec), cend(vec), 6) );
    } 
}
