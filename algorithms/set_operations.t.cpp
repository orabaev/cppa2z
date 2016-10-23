#include <catch.hpp>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

TEST_CASE( "includes", "[std] [algorithm] [sorting] [binary search]" ) {
    
    SECTION( "sorted vec1 contains all elements from sorted vec2" ) {
        const vector<int> vec1{0, 1, 2, 3, 4, 5, 6};
        const vector<int> vec2{2, 3, 6};

        bool found = includes(
                          cbegin(vec1)
                        , cend(vec1)
                        , cbegin(vec2)
                        , cend(vec2)
                     );

        REQUIRE( found );
    } 

    SECTION( "descending sorted vec1 contains all elements from descending sorted vec2" ) {
        const vector<int> vec1{6, 5, 4, 3, 2, 1, 0};
        const vector<int> vec2{5, 2, 0};

        bool found = includes(
                          cbegin(vec1)
                        , cend(vec1)
                        , cbegin(vec2)
                        , cend(vec2)
                        , greater<int>()
                     );

        REQUIRE( found );
    }

}


