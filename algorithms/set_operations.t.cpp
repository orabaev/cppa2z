#include <catch.hpp>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE( "includes", "[std] [algorithm] [sorting] [set operations]" ) {
    
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

TEST_CASE( "inplace_merge", "[std] [algorithm] [sorting] [set operations]" ) {
    
    SECTION( "merge inplace two sorted ranges within vec" ) {
              vector<int>      vec{0, 3, 5,   1, 2, 4, 6};

        const vector<int> expected{0, 1, 2, 3, 4, 5, 6};
        
        auto middle = begin(vec) + 3;
        REQUIRE ( 1 == *middle);

        inplace_merge(begin(vec), middle, end(vec));

        REQUIRE( expected == vec );
    } 

    SECTION( "merge inplace two descending sorted ranges within vec" ) {
              vector<int>      vec{5, 3, 0,   6, 4, 2, 1};

        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};
        
        auto middle = begin(vec) + 3;
        REQUIRE ( 6 == *middle);

        inplace_merge(
              begin(vec)
            , middle
            , end(vec)
            , greater<int>()
        );

        REQUIRE( expected == vec );
    }

}
