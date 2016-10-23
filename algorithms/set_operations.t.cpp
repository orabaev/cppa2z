#include <catch.hpp>
#include <algorithm>
#include <vector>

using namespace std;

TEST_CASE( "includes", "[std] [algorithm] [set operations]" ) {
    
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

TEST_CASE( "inplace_merge", "[std] [algorithm] [set operations]" ) {
    
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

TEST_CASE( "merge", "[std] [algorithm] [set operations]" ) {
    
    SECTION( "merge two sorted ranges into another sorted range" ) {
        const vector<int>    from1{0, 3, 5};
        const vector<int>    from2{1, 2, 4, 6};
              vector<int>       to; 
        const vector<int> expected{0, 1, 2, 3, 4, 5, 6};
        
        merge(
              cbegin(from1)
            , cend(from1)
            , cbegin(from2)
            , cend(from2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "merge two descending sorted ranges into another desending sorted range" ) {
        const vector<int>    from1{5, 3, 0};
        const vector<int>    from2{6, 4, 2, 1};
              vector<int>       to; 
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};
        
        merge(
              cbegin(from1)
            , cend(from1)
            , cbegin(from2)
            , cend(from2)
            , back_inserter(to)
            , greater<int>()
        );

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "set_difference", "[std] [algorithm] [set operations]" ) {
    
    SECTION( "copy elements from sorted vec1 not found in sorted vec2 into another sorted range" ) {
        const vector<int>     vec1{1, 4, 6, 7, 8};
        const vector<int>     vec2{0, 2, 4, 6};
              vector<int>       to; 
        const vector<int> expected{1, 7, 8};
        
        set_difference(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "copy elements from descending sorted vec1 not found in "
             "descending sorted vec2 into another descending sorted range" ) {
        const vector<int>     vec1{8, 7, 6, 4, 1};
        const vector<int>     vec2{6, 4, 2, 0};
              vector<int>       to; 
        const vector<int> expected{8, 7, 1};
        
        set_difference(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
            , greater<int>()
        );

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "set_intersecion", "[std] [algorithm] [set operations]" ) {
    
    SECTION( "copy elements from sorted vec1 found in sorted vec2 into another sorted range" ) {
        const vector<int>     vec1{1, 4, 6, 7, 8};
        const vector<int>     vec2{0, 2, 4, 6};
              vector<int>       to; 
        const vector<int> expected{4, 6};
        
        set_intersection(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "copy elements from descending sorted vec1 found in "
             "descending sorted vec2 into another descending sorted range" ) {
        const vector<int>     vec1{8, 7, 6, 4, 1};
        const vector<int>     vec2{6, 4, 2, 0};
              vector<int>       to; 
        const vector<int> expected{6, 4};
        
        set_intersection(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
            , greater<int>()
        );

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "set_symmetric_difference", "[std] [algorithm] [set operations]" ) {
    
    SECTION( "copy elements from sorted vec1 and sorted vec2 not found "
             "in each other into another sorted range" ) {
        const vector<int>     vec1{1, 4, 6, 7, 8};
        const vector<int>     vec2{0, 2, 4, 6};
              vector<int>       to; 
        const vector<int> expected{0, 1, 2, 7, 8};
        
        set_symmetric_difference(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "copy elements from descending sorted vec1 and descending sorted vec2 "
             "not found in each other into another descending sorted range" ) {
        const vector<int>     vec1{8, 7, 6, 4, 1};
        const vector<int>     vec2{6, 4, 2, 0};
              vector<int>       to; 
        const vector<int> expected{8, 7, 2, 1, 0};
        
        set_symmetric_difference(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
            , greater<int>()
        );

        REQUIRE( expected == to );
    } 

}

TEST_CASE( "set_union", "[std] [algorithm] [set operations]" ) {
    
    SECTION( "create a union by copying elements from sorted vec1 "
             "and sorted vec2 into another sorted range") {
        const vector<int>     vec1{0, 1, 2, 3, 4};
        const vector<int>     vec2{      2, 3, 4, 5, 6};
              vector<int>       to; 
        const vector<int> expected{0, 1, 2, 3, 4, 5, 6};
        
        set_union(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    } 

    SECTION( "create a union from ranges with some duplicate elements"
             "by copying elements from sorted vec1 "
             "and sorted vec2 into another sorted range") {
        const vector<int>     vec1{0, 1, 2, 2, 2, 3, 4};
        const vector<int>     vec2{         2, 2, 3, 4, 5, 6};
              vector<int>       to; 
        const vector<int> expected{0, 1, 2, 2, 2, 3, 4, 5, 6};
        
        set_union(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
        );

        REQUIRE( expected == to );
    }

    SECTION( "create a union by copying elements from descending sorted vec1 "
             "and sdescending orted vec2 into another descending sorted range") {
        const vector<int>     vec1{      4, 3, 2, 1, 0};
        const vector<int>     vec2{6, 5, 4, 3, 2, 1};
              vector<int>       to; 
        const vector<int> expected{6, 5, 4, 3, 2, 1, 0};
        
        set_union(
              cbegin(vec1)
            , cend(vec1)
            , cbegin(vec2)
            , cend(vec2)
            , back_inserter(to)
            , greater<int>()
        );

        REQUIRE( expected == to );
    } 

}
