#include <catch.hpp>
#include <vector>

using namespace std;

TEST_CASE( "is_partitioned", "[std] [algorithm] [partitioning]" ) {
    
    SECTION( "the range is partitioned with first group less than 3" ) {
        const vector<int> vec{2, 0, 1, 3, 5, 4, 7};

        auto less_than_3 = [](int x) { return x < 3; };

        REQUIRE( is_partitioned(cbegin(vec), cend(vec), less_than_3) );
    } 

    SECTION( "the range is not partitioned with first group less than 3" ) {
        const vector<int> vec{3, 0, 1, 3, 5, 4, 7};

        auto less_than_3 = [](int x) { return x < 3; };

        REQUIRE_FALSE( is_partitioned(cbegin(vec), cend(vec), less_than_3) );
    }

}

TEST_CASE( "partition", "[std] [algorithm] [partitioning]" ) {
    
    SECTION( "partition the range with first group less than 3" ) {
              vector<int>         vec{4, 2, 5, 3, 1, 0, 2};
        const vector<int> first_group{0, 1, 2, 2};

        auto less_than_3 = [](int x) { return x < 3; };

        const auto first_it_second_group = partition(begin(vec), end(vec), less_than_3);

        REQUIRE( first_it_second_group != cend(vec) );
        REQUIRE( *first_it_second_group >= 3);

        // BUG? can not use cbegin on GCC TODO check other compiliers
        const auto first_pos_second_group = distance(begin(vec), first_it_second_group);
        REQUIRE( 4 == first_pos_second_group );
        
        bool proper_first_group = is_permutation(cbegin(first_group), cend(first_group), cbegin(vec));
        REQUIRE( proper_first_group ); 
    } 

    SECTION( "partition the range, there is only second group" ) {
        vector<int> vec{4, 7, 5, 3, 4, 4};

        auto less_than_3 = [](int x) { return x < 3; };

        const auto first_it_second_group = partition(begin(vec), end(vec), less_than_3);

        REQUIRE( first_it_second_group == cbegin(vec) );
    }

    SECTION( "partition the range, there is only first group" ) {
        vector<int> vec{1, 0, 2, 2, 1, 0};

        auto less_than_3 = [](int x) { return x < 3; };

        const auto first_it_second_group = partition(begin(vec), end(vec), less_than_3);

        REQUIRE( first_it_second_group == cend(vec) );
    }
}


