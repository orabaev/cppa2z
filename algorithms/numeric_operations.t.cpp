#include <catch.hpp>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE( "accumulate", "[std] [algorithm] [numeric operations]" ) {
    
    SECTION( "compute sum of all elements in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5};

        const int sum = accumulate(begin(vec), end(vec), 0);    
                  
        REQUIRE( 15 == sum  ); 
    } 

    SECTION( "compute product of all elements in the range" ) {
        const vector<int> vec{1, 2, 3, 4, 5};

        auto multiply = [](int x, int y) { return x * y; };
    
        const int product = accumulate(begin(vec), end(vec), 1, multiply);    
                  
        REQUIRE( 120 == product  ); 
    } 

}

